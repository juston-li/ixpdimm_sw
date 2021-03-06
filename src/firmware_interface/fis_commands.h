/*
 * Copyright (c) 2017, Intel Corporation
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

#ifndef CR_MGMT_FIS_COMMANDS_H
#define CR_MGMT_FIS_COMMANDS_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <driver_interface/passthrough.h>

enum fis_error_codes
{
	FIS_ERR_SUCCESS = 0x0,
	FIS_ERR_INVALID_COMMAND_PARAMETER = 0x01,
	FIS_ERR_DATA_TRANSFER_ERROR = 0x02,
	FIS_ERR_INTERNAL_DEVICE_ERROR = 0x03,
	FIS_ERR_UNSUPPORTED_COMMAND = 0x04,
	FIS_ERR_DEVICE_BUSY = 0x05,
	FIS_ERR_INCORRECT_SECURITY_NONCE = 0x06,
	FIS_ERR_FW_AUTHENTICATION_FAILED = 0x07,
	FIS_ERR_INVALID_SECURITY_STATE = 0x08,
	FIS_ERR_SYSTEM_TIME_NOT_SET = 0x09,
	FIS_ERR_DATA_NOT_SET = 0x0A,
	FIS_ERR_ABORTED = 0x0B,
	FIS_ERR_NO_NEW_FW_TO_EXECUTE = 0x0C,
	FIS_ERR_REVISION_FAILURE = 0x0D,
	FIS_ERR_INJECTION_NOT_ENABLED = 0x0E,
	FIS_ERR_CONFIG_LOCKED = 0x0F,
	FIS_ERR_INVALID_ALIGNMENT = 0x10,
	FIS_ERR_INCOMPATIBLE_DIMM_TYPE = 0x11,
	FIS_ERR_TIMEOUT_OCCURRED = 0x12,
	FIS_ERR_RESERVED = 0x13,
	FIS_ERR_MEDIA_DISABLED = 0x14,
	FIS_ERR_FW_UPDATE_ALREADY_OCCURED = 0x15,
	FIS_ERR_NO_RESOURCES_AVAILABLE = 0x16,
};

/*
 * Payloads Structures
 */
struct pt_output_identify_dimm
{
	unsigned short vendor_id;
	unsigned short device_id;
	unsigned short revision_id;
	unsigned short interface_format_code;
	unsigned char firmware_revision[5];
	unsigned char reserved_old_api;
	unsigned char feature_sw_required_mask;
	unsigned char reserved1;
	unsigned short number_of_block_windows;
	unsigned char reserved2[10];
	unsigned int offset_of_block_mode_control_region;
	unsigned int raw_capacity;
	unsigned short manufacturer;
	unsigned int serial_number;
	unsigned char part_number[20];
	unsigned int dimm_sku;
	unsigned short interface_format_code_extra;
	unsigned short api_ver;
	unsigned char reserved3[58];

} __attribute__((packed));
struct pt_output_identify_dimm_characteristics
{
	unsigned short controller_temp_shutdown_threshold;
	unsigned short media_temp_shutdown_threshold;
	unsigned short throttling_start_threshold;
	unsigned short throttling_stop_threshold;
	unsigned char reserved[120];

} __attribute__((packed));
struct pt_output_get_security_state
{
	unsigned char security_state;
	unsigned char reserved[127];

} __attribute__((packed));
struct pt_input_set_passphrase
{
	unsigned char current_passphrase[32];
	unsigned char reserved1[32];
	unsigned char new_passphrase[32];
	unsigned char reserved2[32];

} __attribute__((packed));
struct pt_input_disable_passphrase
{
	unsigned char current_passphrase[32];
	unsigned char reserved[96];

} __attribute__((packed));
struct pt_input_unlock_unit
{
	unsigned char current_passphrase[32];
	unsigned char reserved[96];

} __attribute__((packed));
struct pt_input_secure_erase
{
	unsigned char current_passphrase[32];
	unsigned char reserved[96];

} __attribute__((packed));
struct pt_output_get_alarm_threshold
{
	unsigned short enable;
	unsigned char spare_block_threshold;
	unsigned short media_temp_threshold;
	unsigned short controller_temp_threshold;
	unsigned char reserved[121];

} __attribute__((packed));
struct pt_output_power_management_policy
{
	unsigned char enable;
	unsigned short peak_power_budget;
	unsigned short average_power_budget;
	unsigned char max_power;
	unsigned char reserved[122];

} __attribute__((packed));
struct pt_output_die_sparing_policy
{
	unsigned char enable;
	unsigned char aggressiveness;
	unsigned char supported;
	unsigned char reserved[125];

} __attribute__((packed));
struct pt_output_address_range_scrub
{
	unsigned char enable;
	unsigned char reserved1[3];
	unsigned long long dpa_start_address;
	unsigned long long dpa_end_address;
	unsigned long long dpa_current_address;
	unsigned char reserved2[100];

} __attribute__((packed));
struct pt_output_optional_configuration_data_policy
{
	unsigned char first_fast_refresh;
	unsigned char viral_policy_enabled;
	unsigned char viral_status;
	unsigned char reserved[125];

} __attribute__((packed));
struct pt_output_pmon_registers
{
	unsigned short pmon_retreive_mask;
	unsigned char reserved1[6];
	unsigned int pmon_0_counter;
	unsigned int pmon_0_control;
	unsigned int pmon_1_counter;
	unsigned int pmon_1_control;
	unsigned int pmon_2_counter;
	unsigned int pmon_2_control;
	unsigned int pmon_3_counter;
	unsigned int pmon_3_control;
	unsigned int pmon_4_counter;
	unsigned int pmon_4_control;
	unsigned int pmon_5_counter;
	unsigned int pmon_5_control;
	unsigned int pmon_6_counter;
	unsigned int pmon_6_control;
	unsigned int pmon_7_counter;
	unsigned int pmon_7_control;
	unsigned int pmon_8_counter;
	unsigned int pmon_8_control;
	unsigned int pmon_9_counter;
	unsigned int pmon_9_control;
	unsigned int pmon_10_counter;
	unsigned int pmon_10_control;
	unsigned int pmon_11_counter;
	unsigned int pmon_11_control;
	unsigned int reserved2;
	unsigned int reserved3;
	unsigned int reserved4;
	unsigned int reserved5;
	unsigned int pmon_14_counter;
	unsigned int pmon_14_control;

} __attribute__((packed));
struct pt_input_pmon_registers
{
	unsigned short pmon_retreive_mask;
	unsigned char reserved[126];

} __attribute__((packed));
struct pt_input_set_alarm_threshold
{
	unsigned char enable;
	unsigned short peak_power_budget;
	unsigned short avg_power_budget;
	unsigned char reserved[123];

} __attribute__((packed));
struct pt_output_system_time
{
	unsigned long long unix_time;
	unsigned char reserved[120];

} __attribute__((packed));
struct pt_output_device_identification_v1
{
	unsigned short manufacturer_id;
	unsigned int serial_number;
	unsigned char model_number[20];
	unsigned char reserved[6];

} __attribute__((packed));
struct pt_output_device_identification_v2
{
	unsigned char uid[9];
	unsigned char reserved[23];

} __attribute__((packed));
struct pt_output_id_info_table
{
	unsigned char device_identification[32];
	unsigned long long partition_offset;
	unsigned long long partition_size;

} __attribute__((packed));
struct pt_output_interleave_information_table
{
	unsigned short type;
	unsigned short length;
	unsigned short index;
	unsigned char number_of_dimms;
	unsigned char memory_type;
	unsigned int format;
	unsigned char mirror_enabled;
	unsigned char change_status;
	unsigned char memory_spare;
	unsigned char reserved[9];

} __attribute__((packed));
struct pt_output_partition_size_change_table
{
	unsigned short type;
	unsigned short length;
	unsigned int platform_config_data_partition_size_change_table;
	unsigned long long persistent_memory_partition_size;

} __attribute__((packed));
struct pt_output_current_config_table
{
	unsigned char signature[4];
	unsigned int length;
	unsigned char revision;
	unsigned char checksum;
	unsigned char oem_id[6];
	unsigned char oem_table_id[8];
	unsigned int oem_revision;
	unsigned int creator_id;
	unsigned int creator_revision;
	unsigned short config_status;
	unsigned short reserved;
	unsigned long long volatile_memory_size;
	unsigned long long persistent_memory_size;

} __attribute__((packed));
struct pt_output_config_input_table
{
	unsigned char signature[4];
	unsigned int length;
	unsigned char revision;
	unsigned char checksum;
	unsigned char oem_id[6];
	unsigned char oem_table_id[8];
	unsigned int oem_revision;
	unsigned int creator_id;
	unsigned int creator_revision;
	unsigned int sequence_number;
	unsigned long long reserved;

} __attribute__((packed));
struct pt_output_config_output_table
{
	unsigned char signature[4];
	unsigned int length;
	unsigned char revision;
	unsigned char checksum;
	unsigned char oem_id[6];
	unsigned char oem_table_id[8];
	unsigned int oem_revision;
	unsigned int creator_id;
	unsigned int creator_revision;
	unsigned int sequence_number;
	unsigned char validation_status;
	unsigned char reserved[7];

} __attribute__((packed));
struct pt_output_platform_config_data
{
	unsigned char signature[4];
	unsigned int length;
	unsigned char revision;
	unsigned char checksum;
	unsigned char oem_id[6];
	unsigned char oem_table_id[8];
	unsigned int oem_revision;
	unsigned int creator_id;
	unsigned int creator_revision;
	unsigned int current_config_size;
	unsigned int current_config_offset;
	unsigned int input_config_size;
	unsigned int input_config_offset;
	unsigned int output_config_size;
	unsigned int output_config_offset;
	unsigned char body[131012];

} __attribute__((packed));
struct pt_input_platform_config_data
{
	unsigned char partition_id;
	unsigned char command_option;
	unsigned int offset;
	unsigned char reserved[122];

} __attribute__((packed));
struct pt_output_ns_index
{
	unsigned char signature[16];
	unsigned int flags;
	unsigned int sequence;
	unsigned long long my_offset;
	unsigned long long my_size;
	unsigned long long other_offset;
	unsigned long long label_offset;
	unsigned int nlabel;
	unsigned short label_major_version;
	unsigned short label_minor_version;
	unsigned long long checksum;
	unsigned char free[128];
	unsigned char reserved[56];

} __attribute__((packed));
struct pt_output_ns_label
{
	unsigned char uuid[16];
	unsigned char name[64];
	unsigned int flags;
	unsigned short nlabel;
	unsigned short position;
	unsigned long long iset_cookie;
	unsigned long long lba_size;
	unsigned long long dpa;
	unsigned long long rawsize;
	unsigned int slot;

} __attribute__((packed));
struct pt_output_ns_label_v1_1
{
	struct pt_output_ns_label label;	
	unsigned int unused;

} __attribute__((packed));
struct pt_output_ns_label_v1_2
{
	struct pt_output_ns_label label;	
	unsigned char alignment;
	unsigned char reserved[3];
	unsigned char type_guid[16];
	unsigned char address_abstraction_guid[16];
	unsigned char reserved1[88];
	unsigned long long checksum;

} __attribute__((packed));
struct pt_output_namespace_labels
{
	struct pt_output_ns_index index1;	
	struct pt_output_ns_index index2;	
	unsigned char labels[129536];

} __attribute__((packed));
struct pt_input_namespace_labels
{
	unsigned char partition_id;
	unsigned char command_option;
	unsigned int offset;
	unsigned char reserved[122];

} __attribute__((packed));
struct pt_output_dimm_partition_info
{
	unsigned int volatile_capacity;
	unsigned int reserved0;
	unsigned long long volatile_start;
	unsigned int pm_capacity;
	unsigned int reserved1;
	unsigned long long pm_start;
	unsigned int raw_capacity;
	unsigned int enabled_capacity;
	unsigned char reserved2[88];

} __attribute__((packed));
struct pt_output_fw_debug_log_level
{
	unsigned char log_level;
	unsigned char logs;
	unsigned char reserved[126];

} __attribute__((packed));
struct pt_input_fw_debug_log_level
{
	unsigned char log_id;

} __attribute__((packed));
struct pt_output_fw_load_flag
{
	unsigned char load_flag;

} __attribute__((packed));
struct pt_output_config_lockdown
{
	unsigned char locked;
	unsigned char reserved[127];

} __attribute__((packed));
struct pt_output_ddrt_io_init_info
{
	unsigned char ddrt_io_info;
	unsigned char ddrt_training_complete;
	unsigned char reserverd[126];

} __attribute__((packed));
struct pt_output_get_supported_sku_features
{
	unsigned int dimm_sku;
	unsigned char reserved[124];

} __attribute__((packed));
struct pt_output_enable_dimm
{
	unsigned char enable;
	unsigned char reserved[127];

} __attribute__((packed));
struct pt_output_smart_health_info
{
	unsigned int validation_flags;
	unsigned int reserved0;
	unsigned char health_status;
	unsigned char spare_blocks;
	unsigned char percent_used;
	unsigned char alarm_trips;
	unsigned short media_temp;
	unsigned short controller_temp;
	unsigned int unsafe_shutdown_count;
	unsigned char ait_dram_status;
	unsigned char reserved1[10];
	unsigned char last_shutdown_status;
	unsigned int vendor_specific_data_size;
	unsigned long long power_cycles;
	unsigned long long power_on_time;
	unsigned long long uptime;
	unsigned int unsafe_shutdowns;
	unsigned char last_shutdown_status_details;
	unsigned long long last_shutdown_time;
	unsigned char last_shutdown_status_extended_details[3];
	unsigned int media_error_injections;
	unsigned int non_media_error_injections;
	unsigned char reserved2[44];

} __attribute__((packed));
struct pt_output_firmware_image_info
{
	unsigned char firmware_revision[5];
	unsigned char firmware_type;
	unsigned char reserved0[10];
	unsigned char staged_fw_revision[5];
	unsigned char reserved1;
	unsigned char last_fw_update_status;
	unsigned char reserved2[9];
	unsigned char commit_id[40];
	unsigned char build_configuration[16];
	unsigned char reserved3[40];

} __attribute__((packed));
struct pt_output_firmware_debug_log
{
	unsigned char log_size;
	unsigned char reserved[127];

} __attribute__((packed));
struct pt_input_firmware_debug_log
{
	unsigned char log_action;
	unsigned int log_page_offset;
	unsigned char log_id;
	unsigned char reserved[122];

} __attribute__((packed));
struct pt_output_long_operation_status
{
	unsigned short command;
	unsigned short percent_complete;
	unsigned int estimate_time_to_completion;
	unsigned char status_code;
	unsigned char command_specific_return_data[119];

} __attribute__((packed));
struct pt_output_bsr
{
	unsigned char major_checkpoint;
	unsigned char minor_checkpoint;
	unsigned int rest1;
	unsigned short rest2;

} __attribute__((packed));
struct pt_input_format
{
	unsigned char fill_pattern;
	unsigned char preserve_pdas_write_count;
	unsigned char reserved[126];

} __attribute__((packed));
/*
 * FIS Commands
 */
unsigned int fis_identify_dimm(const unsigned int device_handle, struct pt_output_identify_dimm *p_output_payload);
unsigned int fis_identify_dimm_characteristics(const unsigned int device_handle, struct pt_output_identify_dimm_characteristics *p_output_payload);
unsigned int fis_get_security_state(const unsigned int device_handle, struct pt_output_get_security_state *p_output_payload);
unsigned int fis_set_passphrase(const unsigned int device_handle, struct pt_input_set_passphrase *p_input_payload);
unsigned int fis_disable_passphrase(const unsigned int device_handle, struct pt_input_disable_passphrase *p_input_payload);
unsigned int fis_unlock_unit(const unsigned int device_handle, struct pt_input_unlock_unit *p_input_payload);
unsigned int fis_secure_erase(const unsigned int device_handle, struct pt_input_secure_erase *p_input_payload);
unsigned int fis_freeze_lock(const unsigned int device_handle);
unsigned int fis_get_alarm_threshold(const unsigned int device_handle, struct pt_output_get_alarm_threshold *p_output_payload);
unsigned int fis_power_management_policy(const unsigned int device_handle, struct pt_output_power_management_policy *p_output_payload);
unsigned int fis_die_sparing_policy(const unsigned int device_handle, struct pt_output_die_sparing_policy *p_output_payload);
unsigned int fis_address_range_scrub(const unsigned int device_handle, struct pt_output_address_range_scrub *p_output_payload);
unsigned int fis_optional_configuration_data_policy(const unsigned int device_handle, struct pt_output_optional_configuration_data_policy *p_output_payload);
unsigned int fis_pmon_registers(const unsigned int device_handle, struct pt_input_pmon_registers *p_input_payload, struct pt_output_pmon_registers *p_output_payload);
unsigned int fis_set_alarm_threshold(const unsigned int device_handle, struct pt_input_set_alarm_threshold *p_input_payload);
unsigned int fis_system_time(const unsigned int device_handle, struct pt_output_system_time *p_output_payload);
unsigned int fis_platform_config_data(const unsigned int device_handle, struct pt_input_platform_config_data *p_input_payload, struct pt_output_platform_config_data *p_output_payload);
unsigned int fis_namespace_labels(const unsigned int device_handle, struct pt_input_namespace_labels *p_input_payload, struct pt_output_namespace_labels *p_output_payload);
unsigned int fis_dimm_partition_info(const unsigned int device_handle, struct pt_output_dimm_partition_info *p_output_payload);
unsigned int fis_fw_debug_log_level(const unsigned int device_handle, struct pt_input_fw_debug_log_level *p_input_payload, struct pt_output_fw_debug_log_level *p_output_payload);
unsigned int fis_fw_load_flag(const unsigned int device_handle, struct pt_output_fw_load_flag *p_output_payload);
unsigned int fis_config_lockdown(const unsigned int device_handle, struct pt_output_config_lockdown *p_output_payload);
unsigned int fis_ddrt_io_init_info(const unsigned int device_handle, struct pt_output_ddrt_io_init_info *p_output_payload);
unsigned int fis_get_supported_sku_features(const unsigned int device_handle, struct pt_output_get_supported_sku_features *p_output_payload);
unsigned int fis_enable_dimm(const unsigned int device_handle, struct pt_output_enable_dimm *p_output_payload);
unsigned int fis_smart_health_info(const unsigned int device_handle, struct pt_output_smart_health_info *p_output_payload);
unsigned int fis_firmware_image_info(const unsigned int device_handle, struct pt_output_firmware_image_info *p_output_payload);
unsigned int fis_firmware_debug_log(const unsigned int device_handle, struct pt_input_firmware_debug_log *p_input_payload, struct pt_output_firmware_debug_log *p_output_payload);
unsigned int fis_long_operation_status(const unsigned int device_handle, struct pt_output_long_operation_status *p_output_payload);
unsigned int fis_bsr(const unsigned int device_handle, struct pt_output_bsr *p_output_payload);
unsigned int fis_format(const unsigned int device_handle, struct pt_input_format *p_input_payload);
void fis_get_error_message(unsigned int code, char *message, size_t message_size);

#ifdef __cplusplus
}
#endif
#endif //CR_MGMT_FIS_COMMANDS_H