/*
 * Copyright (c) 2016, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Intel Corporation nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "DeviceService.h"

#include <algorithm>
#include <core/exceptions/NoMemoryException.h>
#include <core/exceptions/LibraryException.h>
#include <LogEnterExit.h>

core::device::DeviceService &core::device::DeviceService::getService()
{
	LogEnterExit(__FUNCTION__, __FILE__, __LINE__);

	// Creating the singleton on class init as a static class member
	// can lead to static initialization order issues.
	// This is a thread-safe form of lazy initialization.
	static DeviceService *pSingleton = new DeviceService();
	return *pSingleton;
}

std::vector<std::string> core::device::DeviceService::getAllUids()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::vector<std::string> result = std::vector<std::string>();
	const std::vector<device_discovery> &discoveries = m_lib.getDevices();

	for(size_t i = 0; i < discoveries.size(); i++)
	{
		result.push_back(Helper::uidToString(discoveries[i].uid));
	}

	return result;
}

std::vector<std::string> core::device::DeviceService::getManageableUids()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::vector<std::string> result = std::vector<std::string>();
	const std::vector<device_discovery> &discoveries = m_lib.getDevices();

	for(size_t i = 0; i < discoveries.size(); i++)
	{
		if(discoveries[i].manageability == MANAGEMENT_VALIDCONFIG)
		{
			result.push_back(Helper::uidToString(discoveries[i].uid));
		}
	}

	return result;
}

core::device::DeviceCollection core::device::DeviceService::getAllDevices()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	DeviceCollection result;

	const std::vector<device_discovery> &discoveries = m_lib.getDevices();
	for(size_t i = 0; i < discoveries.size(); i++)
	{
		Device device(m_lib, discoveries[i]);
		result.push_back(device);
	}

	return result;
}

core::Result<core::device::Device> core::device::DeviceService::getDevice(std::string uid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	Device result(m_lib, m_lib.getDeviceDiscovery(uid));

	return Result<Device>(result);
}

std::vector<std::string> core::device::DeviceService::getUidsForDeviceIds(
		const std::vector<std::string>& deviceIds)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	std::vector<std::string> uids;
	if (deviceIds.size() > 0)
	{
		DeviceCollection devices = getAllDevices();
		for (size_t i = 0; i < deviceIds.size(); i++)
		{
			std::string deviceUid = getUidForDeviceIdFromCollection(
					deviceIds[i],
					devices);
			uids.push_back(deviceUid);
		}
	}

	return uids;
}

std::string core::device::DeviceService::getUidForDeviceIdFromCollection(
		const std::string &deviceId,
		DeviceCollection &devices)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	std::string uid;

	bool found = false;
	for (size_t i = 0; i < devices.size(); i++)
	{
		Device &dev = devices[i];
		std::stringstream handleStr;
		handleStr << dev.getDeviceHandle();

		if (deviceId == dev.getUid() || deviceId == handleStr.str())
		{
			uid = dev.getUid();
			found = true;
			break;
		}
	}

	if (!found)
	{
		throw LibraryException(NVM_ERR_BADDEVICE);
	}

	return uid;
}

std::string core::device::DeviceService::getFirmwareApiVersionByUid(const std::string &deviceUid)
{
	return m_lib.getDeviceDiscovery(deviceUid).fw_api_version;
}

int core::device::DeviceService::dumpDeviceSupport(NVM_UID device_uid, NVM_PATH support_file,
		NVM_SIZE support_file_len, NVM_PATH support_files[NVM_MAX_EAFD_FILES])
{
	int rc = m_lib.dumpDeviceSupport(device_uid, support_file, support_file_len, support_files);

	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return rc;
}
