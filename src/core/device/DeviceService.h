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
#ifndef CR_MGMT_GETDEVICE_H
#define CR_MGMT_GETDEVICE_H

#include <vector>
#include <string>
#include <nvm_types.h>
#include <uid/uid.h>
#include <core/Result.h>
#include "Device.h"
#include <core/Collection.h>

namespace core
{
namespace device
{

class NVM_API DeviceService
{
public:
	DeviceService(NvmLibrary &api = NvmLibrary::getNvmLibrary()) : m_lib(api) { }
	virtual ~DeviceService() {}
	virtual std::vector<std::string> getAllUids();
	virtual std::vector<std::string> getManageableUids();
	virtual std::vector<std::string> getUidsForDeviceIds(const std::vector<std::string> &deviceIds);
	virtual DeviceCollection getAllDevices();
	virtual Result<Device> getDevice(std::string uid);
	virtual std::string getFirmwareApiVersionByUid(const std::string &deviceUid);
	virtual int dumpDeviceSupport(NVM_UID device_uid, NVM_PATH support_file,
			NVM_SIZE support_file_len, NVM_PATH support_files[NVM_MAX_EAFD_FILES]);

	static DeviceService &getService();

protected:
	NvmLibrary &m_lib;

	std::string getUidForDeviceIdFromCollection(const std::string &deviceId,
			DeviceCollection &devices);
};

}
}
#endif //CR_MGMT_GETDEVICE_H
