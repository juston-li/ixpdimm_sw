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

#include "Device.h"
#include <iomanip>
#include <fis_types.h>

namespace core
{
namespace device
{
Device::Device() :
	m_lib(NvmLibrary::getNvmLibrary()),
	m_discovery(device_discovery()),
	m_pDetails(NULL),
	m_pActionRequiredEvents(NULL)
{

}

Device::Device(NvmLibrary &lib, const device_discovery &discovery) :
	m_lib(lib),
	m_pDetails(NULL),
	m_pActionRequiredEvents(NULL)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	memmove(&m_discovery, &discovery, sizeof(m_discovery));
	m_deviceUid = Helper::uidToString(m_discovery.uid);
}

Device::Device(const Device &other) :
	m_lib(other.m_lib),
	m_pDetails(NULL),
	m_pActionRequiredEvents(NULL)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	copy(other);
}

Device &Device::operator=(const Device &other)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	if (&other == this)
		return *this;

	copy(other);

	return *this;
}

void Device::copy(const Device &other)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	this->m_lib = other.m_lib;
	this->m_discovery = other.m_discovery;
	this->m_deviceUid = other.m_deviceUid;
	if (other.m_pDetails)
	{
		this->m_pDetails = new device_details();
		memmove(this->m_pDetails, other.m_pDetails, sizeof(device_details));
	}

	if (other.m_pActionRequiredEvents)
	{
		this->m_pActionRequiredEvents = new std::vector<event>();
		for (size_t i = 0; i < other.m_pActionRequiredEvents->size(); i++)
		{
			(*this->m_pActionRequiredEvents).push_back((*other.m_pActionRequiredEvents)[i]);
		}
	}
}

Device::~Device()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	if (m_pDetails)
	{
		delete m_pDetails;
	}
	if (m_pActionRequiredEvents)
	{
		delete m_pActionRequiredEvents;
	}
}

Device *Device::clone() const
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return new Device(*this);
}


enum manageability_state Device::getManageabilityState()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().manageability;
}

std::string Device::getUid()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return Helper::uidToString(getDiscovery().uid);
}

enum memory_type Device::getMemoryType()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().memory_type;
}

bool Device::isManageable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getManageabilityState() == MANAGEMENT_VALIDCONFIG;
}

enum lock_state Device::getLockState()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().lock_state;
}

NVM_UINT32 Device::getDeviceHandle()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_handle.handle;
}

enum device_health Device::getDeviceStatusHealth()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.health;
}

NVM_UINT32 Device::getChannelPosition()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_handle.parts.mem_channel_dimm_num;
}

enum config_status Device::getConfigStatus()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.config_status;
}

enum device_ars_status Device::getArsStatus()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.ars_status;
}

enum device_sanitize_status Device::getSanitizeStatus()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.sanitize_status;
}

NVM_UINT32 Device::getChannelId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_handle.parts.mem_channel_id;
}

enum device_form_factor Device::getFormFactor()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().form_factor;
}

NVM_UINT16 Device::getPhysicalId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().physical_id;
}

NVM_UINT16 Device::getVendorId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().vendor_id;
}

NVM_UINT16 Device::getDeviceId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_id;
}

NVM_UINT16 Device::getRevisionId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().revision_id;
}

NVM_UINT16 Device::getSocketId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().socket_id;
}

NVM_UINT16 Device::getMemoryControllerId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().memory_controller_id;
}
NVM_UINT16 Device::getNodeControllerId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().node_controller_id;
}

std::string Device::getSerialNumber()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	char serialNumStr[NVM_SERIALSTR_LEN];
	unsigned char displaySerialNumber[NVM_SERIAL_LEN];

	swap_bytes(displaySerialNumber, (unsigned char *)getDiscovery().serial_number,
			NVM_SERIAL_LEN);

	SERIAL_NUMBER_TO_STRING(displaySerialNumber, serialNumStr);
	return std::string(serialNumStr);
}

NVM_UINT16 Device::getSubsystemVendor()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().subsystem_vendor_id;
}

NVM_UINT16 Device::getSubsystemDevice()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().subsystem_device_id;
}

NVM_UINT16 Device::getSubsystemRevision()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().subsystem_revision_id;
}

bool Device::isManufacturingInfoValid()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	if (getDiscovery().manufacturing_info_valid  == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

NVM_UINT8 Device::getManufacturingLoc()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().manufacturing_location;
}

NVM_UINT16 Device::getManufacturingDate()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().manufacturing_date;
}

std::string Device::getManufacturer()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::string result = "Undefined";
	char manufacturerStr[NVM_MANUFACTURERSTR_LEN];

	if (lookup_jedec_jep106_manufacturer(
		getDiscovery().manufacturer, NVM_MANUFACTURER_LEN,
		manufacturerStr, NVM_MANUFACTURERSTR_LEN) == COMMON_SUCCESS)
	{
		result = std::string(manufacturerStr);
	}
	return result;
}

NVM_UINT16 Device::getManufacturerId()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	unsigned char manufacturer[NVM_MANUFACTURER_LEN];

	swap_bytes((unsigned char *)manufacturer, (unsigned char *)getDiscovery().manufacturer,
			NVM_MANUFACTURER_LEN);

	return MANUFACTURER_TO_UINT(manufacturer);
}

std::string Device::getPartNumber()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().part_number;
}

std::string Device::getFwRevision()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().fw_revision;
}

std::string Device::getFwApiVersion()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().fw_api_version;
}

fw_log_level Device::getFwLogLevel()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	fw_log_level result = FW_LOG_LEVEL_UNKNOWN;
	try
	{
		result = m_lib.getFwLogLevel(m_deviceUid);
	}
	catch (core::LibraryException &)
	{
		// don't rethrow
	}

	return result;
}

NVM_UINT64 Device::getRawCapacity()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().capacity;
}

std::vector<NVM_UINT16> Device::getInterfaceFormatCodes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::vector<NVM_UINT16> interfaceFormatCodes;
	for (int i = 0; i < NVM_MAX_IFCS_PER_DIMM; i++)
	{
		NVM_UINT16 ifc = getDiscovery().interface_format_codes[i];
		if (ifc != FORMAT_NONE)
		{
			interfaceFormatCodes.push_back(ifc);
		}
	}
	return interfaceFormatCodes;
}

bool Device::isPassphraseCapable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().security_capabilities.passphrase_capable;
}

bool Device::isUnlockDeviceCapable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().security_capabilities.unlock_device_capable;
}

bool Device::isEraseCryptoCapable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().security_capabilities.erase_crypto_capable;
}

std::vector<NVM_UINT16> Device::getSecurityCapabilities()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::vector<NVM_UINT16> result;
	if (isPassphraseCapable())
	{
		result.push_back(SECURITY_PASSPHRASE);
	}
	if (isUnlockDeviceCapable())
	{
		result.push_back(SECURITY_UNLOCK);
	}
	if (isEraseCryptoCapable())
	{
		result.push_back(SECURITY_ERASE);
	}

	return result;
}

bool Device::isDieSparingCapable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_capabilities.die_sparing_capable;
}

bool Device::isAppDirectModeCapable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_capabilities.app_direct_mode_capable;
}

bool Device::isMemoryModeCapable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().device_capabilities.memory_mode_capable;
}

std::vector<NVM_UINT16> Device::getMemoryCapabilities()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::vector<NVM_UINT16> result;

	if (isMemoryModeCapable())
	{
		result.push_back(MEMORY_CAPABILITY_MEMORYMODE);
	}
	if (isAppDirectModeCapable())
	{
		result.push_back(MEMORYTYPE_CAPABILITY_APPDIRECTMODE);
	}
	return result;
}

NVM_UINT32 Device::getSku()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDiscovery().dimm_sku;
}

NVM_UINT16 Device::getHealthState()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	NVM_UINT16 healthState = isManageable() ? getDeviceStatusHealth()
											: DEVICE_HEALTH_UNMANAGEABLE;
	return healthState;
}

bool Device::isNew()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.is_new;
}

bool Device::getIsMissing()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.is_missing;
}

NVM_UINT8 Device::getDieSparesAvailable()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.die_spares_available;
}

std::vector<NVM_UINT16> Device::getLastShutdownStatus()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	std::vector<NVM_UINT16> result;

	NVM_UINT8 lastShutdownState = getDetails().status.last_shutdown_status;
	if (lastShutdownState == SHUTDOWN_STATUS_UNKNOWN)
	{
		result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_UKNOWN);
	}
	else // can't be "Unknown" and "Known"
	{
		if (lastShutdownState & SHUTDOWN_STATUS_CLEAN)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_FW_FLUSH_COMPLETE);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_PM_ADR)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_PM_ADR_COMMAND);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_PM_S3)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_PM_S3);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_PM_S5)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_PM_S5);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_DDRT_POWER_FAIL)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_DDRT_POWER_FAIL);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_PMIC_12V_POWER_FAIL)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_PMIC_12V_POWER_FAIL);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_WARM_RESET)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_PM_WARM_RESET);
		}
		if (lastShutdownState & SHUTDOWN_STATUS_FORCED_THERMAL)
		{
			result.push_back(DEVICE_LAST_SHUTDOWN_STATUS_THERMAL_SHUTDOWN);
		}
	}

	return result;
}

NVM_UINT64 Device::getLastShutdownTime()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.last_shutdown_time;
}

bool Device::isMixedSku()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.mixed_sku;
}

bool Device::isSkuViolation()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.sku_violation;
}

time_t Device::getPerformanceTime()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.time;
}

NVM_UINT64 Device::getBytesRead()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.bytes_read;
}

NVM_UINT64 Device::getHostReads()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.host_reads;
}

NVM_UINT64 Device::getBytesWritten()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.bytes_written;
}

NVM_UINT64 Device::getHostWrites()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.host_writes;
}

NVM_UINT64 Device::getBlockReads()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.block_reads;
}

NVM_UINT64 Device::getBlockWrites()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().performance.block_writes;
}

NVM_UINT64 Device::getTotalCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.capacity;
}

NVM_UINT64 Device::getMemoryCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.memory_capacity;
}

NVM_UINT64 Device::getAppDirectCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.app_direct_capacity;
}

NVM_UINT64 Device::getStorageCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.storage_capacity;
}

NVM_UINT64 Device::getUnconfiguredCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.unconfigured_capacity;
}

NVM_UINT64 Device::getInaccessibleCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.inaccessible_capacity;
}

NVM_UINT64 Device::getReservedCapacityBytes()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().capacities.reserved_capacity;
}

NVM_UINT64 Device::getDataWidth()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().data_width;
}

NVM_UINT64 Device::getTotalWidth()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().total_width;
}

NVM_UINT64 Device::getSpeed()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().speed;
}

bool Device::isPowerManagementEnabled()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().power_management_enabled;
}

NVM_UINT8 Device::getPowerLimit()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().power_limit;
}

NVM_UINT16 Device::getPeakPowerBudget()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().peak_power_budget;
}

NVM_UINT16 Device::getAvgPowerBudget()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().avg_power_budget;
}

bool Device::isDieSparingEnabled()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().die_sparing_enabled;
}

NVM_UINT8 Device::getDieSparingLevel()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().die_sparing_level;
}

std::string Device::getDeviceLocator()
{
	return std::string(getDetails().device_locator);
}

std::string Device::getBankLabel()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return std::string(getDetails().bank_label);
}

bool Device::isFirstFastRefresh()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().settings.first_fast_refresh;
}

bool Device::isViralPolicyEnabled()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().settings.viral_policy;
}

bool Device::getCurrentViralState()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.viral_state;
}

bool Device::isActionRequired()
{
	return getEvents().size() > 0;
}

std::vector<event> Device::getActionRequiredEvents()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getEvents();
}

enum fw_update_status Device::getFwUpdateStatus()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().fw_info.fw_update_status;
}

bool Device::isAitDramEnabled()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.ait_dram_enabled;
}

std::vector<NVM_UINT16> Device::getBootStatus()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	std::vector<NVM_UINT16> result;
	NVM_UINT64 bootStatus = getDetails().status.boot_status;


	if (BSR_IS_INVALID(bootStatus))
	{
		result.push_back(DEVICE_BOOT_STATUS_UNKNOWN);
	}
	else
	{
		if (!BSR_MEDIA_READY_STATUS(bootStatus))
		{
			result.push_back(DEVICE_BOOT_STATUS_MEDIA_NOT_READY);
		}

		if (BSR_MEDIA_ERROR(bootStatus))
		{
			result.push_back(DEVICE_BOOT_STATUS_MEDIA_ERROR);
		}

		if (BSR_MEDIA_DISABLED(bootStatus))
		{
			result.push_back(DEVICE_BOOT_STATUS_MEDIA_DISABLED);
		}

		if (BSR_H_ASSERTION(bootStatus))
		{
			result.push_back(DEVICE_BOOT_STATUS_FW_ASSERT);
		}

		if (result.empty())
		{
			result.push_back(DEVICE_BOOT_STATUS_SUCCESS);
		}
	}

	return result;
}

NVM_UINT32 Device::getInjectedMediaErrors()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.injected_media_errors;
}

NVM_UINT32 Device::getInjectedNonMediaErrors()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return getDetails().status.injected_non_media_errors;
}

const device_discovery &Device::getDiscovery()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	return m_discovery;
}

const device_details &Device::getDetails()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	if (m_pDetails == NULL)
	{
		m_pDetails = new device_details();
		try
		{
			const device_details &details = m_lib.getDeviceDetails(m_deviceUid);
			memmove(m_pDetails, &details, sizeof(details));
		}
		catch (core::LibraryException &e)
		{
			if (e.getErrorCode() != NVM_ERR_NOTMANAGEABLE)
			{
				throw;
			}
		}

	}
	return *m_pDetails;
}

const std::vector<event> &Device::getEvents()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	if (m_pActionRequiredEvents == NULL)
	{
		m_pActionRequiredEvents = new std::vector<event>();
		event_filter filter;
		memset(&filter, 0, sizeof(filter));
		filter.filter_mask = NVM_FILTER_ON_AR | NVM_FILTER_ON_UID;
		filter.action_required = 1;
		memmove(filter.uid, getDiscovery().uid, sizeof(filter.uid));

		try
		{
			*m_pActionRequiredEvents = m_lib.getEvents(filter);
		}
		catch (core::LibraryException &)
		{
			// don't throw
		}
	}
	return *m_pActionRequiredEvents;
}

std::string Device::getFormattedManufacturingDate(NVM_UINT16 manufacturingdate)
{
    LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
    NVM_UINT8 week_byte = (NVM_UINT8)(manufacturingdate >> 8);
    NVM_UINT8 year_byte = (NVM_UINT8)(manufacturingdate & 0x00FF);

    NVM_UINT8 week_dec_byte = bcd_byte_to_dec(week_byte);
    NVM_UINT8 year_dec_byte = bcd_byte_to_dec(year_byte);

    std::stringstream date_str;

    if (week_dec_byte == 0xFF || year_dec_byte == 0xFF)
    {
        week_dec_byte = 0;
        year_dec_byte = 0;
    }

    date_str << std::setfill('0');
    date_str << std::setw(2) << (NVM_UINT32)week_dec_byte;
    date_str << "-";
    date_str << std::setw(2) << (NVM_UINT32)year_dec_byte;
    return date_str.str();
}

}
}
