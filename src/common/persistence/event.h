/*
 * Copyright (c) 2015 2016, Intel Corporation
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

/*
 * This file contains the definition of the common eventing functionality.
 */

#ifndef	_EVENT_H_
#define	_EVENT_H_

#include <common_types.h>
#include <nvm_management.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	MAX_EVENT_SUBSCRIBERS	5 //!< Maximum number of event subscribers.
#define	EVENT_CODE_OFFSET(type)	(type * 100)

#define	EVENT_CODE_OFFSET_MGMT			EVENT_CODE_OFFSET(EVENT_TYPE_MGMT)

/*
 * Event codes for events logged by management software
 */
enum event_code_mgmt
{
	EVENT_CODE_MGMT_CONFIG_GOAL_CREATED = EVENT_CODE_OFFSET_MGMT + 0,
	EVENT_CODE_MGMT_CONFIG_GOAL_DELETED = EVENT_CODE_OFFSET_MGMT + 1,
	EVENT_CODE_MGMT_NAMESPACE_CREATED = EVENT_CODE_OFFSET_MGMT + 2,
	EVENT_CODE_MGMT_NAMESPACE_DELETED = EVENT_CODE_OFFSET_MGMT + 3,
	EVENT_CODE_MGMT_NAMESPACE_MODIFIED = EVENT_CODE_OFFSET_MGMT + 4,
	EVENT_CODE_MGMT_SENSOR_SETTINGS_CHANGE = EVENT_CODE_OFFSET_MGMT + 5,
	EVENT_CODE_MGMT_FIRMWARE_UPDATE = EVENT_CODE_OFFSET_MGMT + 6,
	EVENT_CODE_MGMT_SECURITY_PASSWORD_SET = EVENT_CODE_OFFSET_MGMT + 7,
	EVENT_CODE_MGMT_SECURITY_PASSWORD_REMOVED = EVENT_CODE_OFFSET_MGMT + 8,
	EVENT_CODE_MGMT_SECURITY_SECURE_ERASE = EVENT_CODE_OFFSET_MGMT + 9,
	EVENT_CODE_MGMT_SECURITY_FROZEN = EVENT_CODE_OFFSET_MGMT + 10,

	// For checking event code validity
	EVENT_CODE_MGMT_UNKNOWN = EVENT_CODE_OFFSET_MGMT + 11
};

#define	EVENT_CODE_OFFSET_DIAG_QUICK	EVENT_CODE_OFFSET(EVENT_TYPE_DIAG_QUICK)

/*
 * Event codes for quick diagnostic test events
 */
enum event_code_diag_quick
{
	// success
	EVENT_CODE_DIAG_QUICK_SUCCESS = EVENT_CODE_OFFSET_DIAG_QUICK + 0,
	// error
	EVENT_CODE_DIAG_QUICK_BAD_HEALTH = EVENT_CODE_OFFSET_DIAG_QUICK + 4,
	EVENT_CODE_DIAG_QUICK_BAD_MEDIA_TEMP = EVENT_CODE_OFFSET_DIAG_QUICK + 5,
	EVENT_CODE_DIAG_QUICK_BAD_SPARE = EVENT_CODE_OFFSET_DIAG_QUICK + 6,
	EVENT_CODE_DIAG_QUICK_BAD_PERCENT_USED = EVENT_CODE_OFFSET_DIAG_QUICK + 7,
	EVENT_CODE_DIAG_QUICK_BAD_UNCORRECTABLE_MEDIA_ERRORS = EVENT_CODE_OFFSET_DIAG_QUICK + 8,
	EVENT_CODE_DIAG_QUICK_BAD_CORRECTED_MEDIA_ERRORS = EVENT_CODE_OFFSET_DIAG_QUICK + 9,
	EVENT_CODE_DIAG_QUICK_BAD_ERASURE_CODED_CORRECTED_MEDIA_ERRORS = EVENT_CODE_OFFSET_DIAG_QUICK + 10,
	EVENT_CODE_DIAG_QUICK_BAD_CORE_TEMP = EVENT_CODE_OFFSET_DIAG_QUICK + 11,
	EVENT_CODE_DIAG_QUICK_BAD_POWER_LIMITATION = EVENT_CODE_OFFSET_DIAG_QUICK + 12,
	EVENT_CODE_DIAG_QUICK_UNREADABLE_BSR = EVENT_CODE_OFFSET_DIAG_QUICK + 13,
	EVENT_CODE_DIAG_QUICK_MEDIA_NOT_READY = EVENT_CODE_OFFSET_DIAG_QUICK + 14,
	EVENT_CODE_DIAG_QUICK_MEDIA_READY_ERROR = EVENT_CODE_OFFSET_DIAG_QUICK + 15,
	EVENT_CODE_DIAG_QUICK_DDRT_IO_INIT_NOT_READY = EVENT_CODE_OFFSET_DIAG_QUICK + 16,
	EVENT_CODE_DIAG_QUICK_DDRT_IO_INIT_ERROR = EVENT_CODE_OFFSET_DIAG_QUICK + 17,
	EVENT_CODE_DIAG_QUICK_MAILBOX_INTERFACE_NOT_READY = EVENT_CODE_OFFSET_DIAG_QUICK + 18,
	EVENT_CODE_DIAG_QUICK_NO_POST_CODE = EVENT_CODE_OFFSET_DIAG_QUICK + 19,
	EVENT_CODE_DIAG_QUICK_FW_INITIALIZATION_INCOMPLETE = EVENT_CODE_OFFSET_DIAG_QUICK + 20,
	EVENT_CODE_DIAG_QUICK_FW_HIT_ASSERT = EVENT_CODE_OFFSET_DIAG_QUICK + 21,
	EVENT_CODE_DIAG_QUICK_FW_STALLED = EVENT_CODE_OFFSET_DIAG_QUICK + 22,
	EVENT_CODE_DIAG_QUICK_VIRAL_STATE = EVENT_CODE_OFFSET_DIAG_QUICK + 23,
	EVENT_CODE_DIAG_QUICK_BAD_DRIVER = EVENT_CODE_OFFSET_DIAG_QUICK + 24,
	EVENT_CODE_DIAG_QUICK_NOT_MANAGEABLE = EVENT_CODE_OFFSET_DIAG_QUICK + 25,
	EVENT_CODE_DIAG_QUICK_BAD_MEDIA_TEMP_THROTTLING = EVENT_CODE_OFFSET_DIAG_QUICK + 26,
	EVENT_CODE_DIAG_QUICK_BAD_MEDIA_TEMP_SHUTDOWN = EVENT_CODE_OFFSET_DIAG_QUICK + 27,
	EVENT_CODE_DIAG_QUICK_BAD_CORE_TEMP_SHUTDOWN = EVENT_CODE_OFFSET_DIAG_QUICK + 28,
	EVENT_CODE_DIAG_QUICK_SPARE_DIE_CONSUMED = EVENT_CODE_OFFSET_DIAG_QUICK + 29,
	EVENT_CODE_DIAG_QUICK_UNSAFE_SHUTDOWN = EVENT_CODE_OFFSET_DIAG_QUICK + 30,
	EVENT_CODE_DIAG_QUICK_SANITIZE_IN_PROGRESS = EVENT_CODE_OFFSET_DIAG_QUICK + 31,
	EVENT_CODE_DIAG_QUICK_SANITIZE_COMPLETE = EVENT_CODE_OFFSET_DIAG_QUICK + 32,
	EVENT_CODE_DIAG_QUICK_AIT_DRAM_NOT_READY = EVENT_CODE_OFFSET_DIAG_QUICK + 33,
	EVENT_CODE_DIAG_QUICK_MEDIA_DISABLED = EVENT_CODE_OFFSET_DIAG_QUICK + 34,

	EVENT_CODE_DIAG_QUICK_UNKNOWN
};

#define	EVENT_CODE_OFFSET_DIAG_SECURITY	EVENT_CODE_OFFSET(EVENT_TYPE_DIAG_SECURITY)

/*
 * Event codes for security diagnostic test events
 */
enum event_code_diag_security
{
	// success
	EVENT_CODE_DIAG_SECURITY_SUCCESS =
			EVENT_CODE_OFFSET_DIAG_SECURITY + 0,
	// aborted
	EVENT_CODE_DIAG_SECURITY_NO_DIMMS =
			EVENT_CODE_OFFSET_DIAG_SECURITY + 1,
	// error
	EVENT_CODE_DIAG_SECURITY_INCONSISTENT =
			EVENT_CODE_OFFSET_DIAG_SECURITY + 2,
	EVENT_CODE_DIAG_SECURITY_ALL_DISABLED =
			EVENT_CODE_OFFSET_DIAG_SECURITY + 3,
	EVENT_CODE_DIAG_SECURITY_ALL_NOTSUPPORTED =
			EVENT_CODE_OFFSET_DIAG_SECURITY + 4,

	// for checking validity of code
	EVENT_CODE_DIAG_SECURITY_UNKNOWN =
			EVENT_CODE_OFFSET_DIAG_SECURITY + 5
};

#define	EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY	EVENT_CODE_OFFSET(EVENT_TYPE_DIAG_FW_CONSISTENCY)

/*
 * Event codes for firmware consistency and settings check diagnostic test events
 */
enum event_code_diag_fw_consistency
{
	// success
	EVENT_CODE_DIAG_FW_SUCCESS = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 0,
	// aborted
	EVENT_CODE_DIAG_FW_NO_DIMMS = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 1,
	// error
	EVENT_CODE_DIAG_FW_INCONSISTENT = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 2,
	EVENT_CODE_DIAG_FW_BAD_TEMP_MEDIA_THRESHOLD = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 3,
	EVENT_CODE_DIAG_FW_BAD_TEMP_CONTROLLER_THRESHOLD = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 4,
	EVENT_CODE_DIAG_FW_BAD_SPARE_BLOCK = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 5,
	EVENT_CODE_DIAG_FW_BAD_FW_LOG_LEVEL = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 6,
	EVENT_CODE_DIAG_FW_SYSTEM_TIME_DRIFT = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 7,
	EVENT_CODE_DIAG_FW_BAD_POWER_MGMT_POLICY = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 8,
	EVENT_CODE_DIAG_FW_BAD_DIE_SPARING_POLICY = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 9,

	// for checking validity of code
	EVENT_CODE_DIAG_FW_UNKNOWN = EVENT_CODE_OFFSET_DIAG_FW_CONSISTENCY + 10
};

#define	EVENT_CODE_OFFSET_HEALTH	EVENT_CODE_OFFSET(EVENT_TYPE_HEALTH)

enum event_code_health
{
	EVENT_CODE_HEALTH_NEW_MEDIAERRORS_FOUND = EVENT_CODE_OFFSET_HEALTH + 0,
	EVENT_CODE_HEALTH_HEALTH_STATE_CHANGED = EVENT_CODE_OFFSET_HEALTH + 1,
	EVENT_CODE_HEALTH_NAMESPACE_HEALTH_STATE_CHANGED = EVENT_CODE_OFFSET_HEALTH + 2,
	EVENT_CODE_HEALTH_NEW_FWERRORS_FOUND = EVENT_CODE_OFFSET_HEALTH + 3,
	EVENT_CODE_HEALTH_SANITIZE_INPROGRESS = EVENT_CODE_OFFSET_HEALTH + 4,
	EVENT_CODE_HEALTH_SANITIZE_COMPLETE = EVENT_CODE_OFFSET_HEALTH + 5,
	EVENT_CODE_HEALTH_UNKNOWN
};

#define	EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG	EVENT_CODE_OFFSET(EVENT_TYPE_DIAG_PLATFORM_CONFIG)

/*
 * Event codes for quick diagnostic test events
 */
enum event_code_diag_platform_config
{
	// success
	EVENT_CODE_DIAG_PCONFIG_SUCCESS = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 0,
	// aborted
	EVENT_CODE_DIAG_PCONFIG_NO_DIMMS = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 1,
	// error
	EVENT_CODE_DIAG_PCONFIG_INVALID_NFIT = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 2,
	EVENT_CODE_DIAG_PCONFIG_INVALID_PCAT = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 3,
	EVENT_CODE_DIAG_PCONFIG_INVALID_PCD = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 4,
	EVENT_CODE_DIAG_PCONFIG_INVALID_CURRENT_PCD = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 5,
	EVENT_CODE_DIAG_PCONFIG_UNCONFIGURED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 6,
	EVENT_CODE_DIAG_PCONFIG_BROKEN_ISET = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 7,
	EVENT_CODE_DIAG_PCONFIG_MAPPED_CAPACITY = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 8,
	EVENT_CODE_DIAG_PCONFIG_REBOOT_NEEDED_TO_APPLY_GOAL = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 9,
	EVENT_CODE_DIAG_PCONFIG_APP_DIRECT_NAMESPACE_TOO_SMALL = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 10,
	EVENT_CODE_DIAG_PCONFIG_POOL_NEEDS_APP_DIRECT_NAMESPACES = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 11,
	EVENT_CODE_DIAG_PCONFIG_POOL_NEEDS_STORAGE_NAMESPACES = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 12,
	EVENT_CODE_DIAG_PCONFIG_DIMM_CONFIG_UNBALANCED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 13,
	EVENT_CODE_DIAG_PCONFIG_DIMMS_DIFFERENT_SIZES = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 14,
	EVENT_CODE_DIAG_PCONFIG_DIMM_SECURITY_SKUS_MIXED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 15,
	EVENT_CODE_DIAG_PCONFIG_DIMM_MODE_SKUS_MIXED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 16,
	EVENT_CODE_DIAG_PCONFIG_DIMM_DIE_SPARING_SKUS_MIXED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 17,
	EVENT_CODE_DIAG_PCONFIG_DIMM_INIT_FAILED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 18,
	EVENT_CODE_DIAG_PCONFIG_DIMM_SKU_VIOLATION = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 19,
	EVENT_CODE_DIAG_PCONFIG_DIMM_GOAL_SKU_VIOLATION = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 20,
	EVENT_CODE_DIAG_PCONFIG_POOLS_FAILED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 21,
	EVENT_CODE_DIAG_PCONFIG_NAMESPACES_FAILED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 22,
	EVENT_CODE_DIAG_PCONFIG_NO_BIOS_CONFIG_SUPPORT = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 23,
	EVENT_CODE_DIAG_PCONFIG_GOAL_FAILED_CONFIG_ERROR = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 24,
	EVENT_CODE_DIAG_PCONFIG_GOAL_FAILED_INSUFFICIENT_RESOURCES = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 25,
	EVENT_CODE_DIAG_PCONFIG_GOAL_FAILED_FW_ERROR = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 26,
	EVENT_CODE_DIAG_PCONFIG_GOAL_FAILED_UNKNOWN = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 27,
	EVENT_CODE_DIAG_PCONFIG_BROKEN_ISET_MOVED = EVENT_CODE_OFFSET_DIAG_PLATFORM_CONFIG + 28,
	EVENT_CODE_DIAG_PCONFIG_UNKNOWN
};

#define	EVENT_CODE_OFFSET_CONFIG	EVENT_CODE_OFFSET(EVENT_TYPE_CONFIG)

/*
 * Event codes for NVM-DIMM status events
 */
enum event_code_config
{
	EVENT_CODE_CONFIG_GOAL_APPLIED = EVENT_CODE_OFFSET_CONFIG + 0,
	EVENT_CODE_CONFIG_TOPOLOGY_ADDED_CONFIGURED_DEVICE = EVENT_CODE_OFFSET_CONFIG + 1,
	EVENT_CODE_CONFIG_TOPOLOGY_ADDED_NEW_DEVICE = EVENT_CODE_OFFSET_CONFIG + 2,
	EVENT_CODE_CONFIG_TOPOLOGY_MISSING_DEVICE = EVENT_CODE_OFFSET_CONFIG + 3,
	EVENT_CODE_CONFIG_TOPOLOGY_REPLACED_CONFIGURED_DEVICE = EVENT_CODE_OFFSET_CONFIG + 4,
	EVENT_CODE_CONFIG_TOPOLOGY_REPLACED_NEW_DEVICE = EVENT_CODE_OFFSET_CONFIG + 5,
	EVENT_CODE_CONFIG_TOPOLOGY_MOVED_DEVICE = EVENT_CODE_OFFSET_CONFIG + 6,

	// For checking event code validity
	EVENT_CODE_CONFIG_UNKNOWN
};

/*
 * Store an event log entry in the db
 */
int store_event(struct event *p_event, COMMON_BOOL syslog);

/*
 * Helper method to convert event info into a struct to store in the db
 */
int store_event_by_parts(const enum event_type type,
		const enum event_severity severity, const NVM_UINT16 code,
		const NVM_UID device_uid, const NVM_BOOL action_required, const NVM_EVENT_ARG arg1,
		const NVM_EVENT_ARG arg2, const NVM_EVENT_ARG arg3,
		const enum diagnostic_result result);

/*
 * Log an event in the syslog
 * @remark Checks the config DB to see if we should log the event to syslog
 * @return whether it logged to syslog
 */
NVM_BOOL log_event_in_syslog(const struct event *p_event, const char *source);

/*
 * Populate the event message based on the type and code
 */
void populate_event_message(struct event *p_event);

/*
 * Retrieve all events from the database and then filter on the specified
 * filter.
 * If purge is 1, delete the matching event from the database
 * Else if p_events is NULL or count = 0, just count the number matching.
 * Else copy to the provided structure.
 * Returns the count of matching events.
 */
int process_events_matching_filter(const struct event_filter *p_filter,
		struct event *p_events, const NVM_UINT16 count, const NVM_BOOL purge);

/*!
 * Acknowledge all events that meet the filter criteria
 */
int acknowledge_events(struct event_filter *p_filter);

#ifdef __cplusplus
}
#endif

#endif  /* _EVENT_H_ */
