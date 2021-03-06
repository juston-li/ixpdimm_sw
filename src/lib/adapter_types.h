/*
 * Copyright (c) 2015 2017, Intel Corporation
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
 * This file defines the structures used by the interface between the Native API
 * and the driver implementation.
 */

#ifndef ADAPTER_TYPES_H_
#define	ADAPTER_TYPES_H_

#include "nvm_types.h"

#define	MAX_NUMBER_OF_BLOCK_SIZES 16
#define	MAX_DIAGNOSTIC_RESULTS 1024

/*
 * ------------------------------------------------------------------------------------------------
 * Enums
 * ------------------------------------------------------------------------------------------------
 */

#define	NVM_DETAILS_SIZE_UNKNOWN	(NVM_UINT64)-1

/*
 * Describes the memory type associated with the DIMM
 * From DMTF SMBIOS spec
 * 7.18.2 Memory Device - Type
 */
enum smbios_memory_type
{
	// TODO: from SMBIOS 7.18.2 Memory Device <97> Type, NGNVM value TBD
	SMBIOS_MEMORY_TYPE_NVMDIMM = 0x15,
	SMBIOS_MEMORY_TYPE_DDR4 = 0x1A
};

enum smbios_memory_type_detail
{
	SMBIOS_MEMORY_TYPE_DETAIL_NONVOLATILE = 1 << 12
};

enum smbios_form_factor
{
	SMBIOS_FORM_FACTOR_DIMM = 0x9,
	SMBIOS_FORM_FACTOR_SODIMM = 0xD
};

/*
 * Defines driver specific diagnostics
 */
enum driver_diagnostic
{
	DRIVER_DIAGNOSTIC_PM_METADATA_CHECK = 0
};

/*
 * Defines type of the result from a driver metadata check diagnostic
 */
enum driver_diagnostic_health_event_type
{

	HEALTH_EVENT_TYPE_UNKNOWN = 0,
	HEALTH_EVENT_TYPE_NAMESPACE = 1,
	HEALTH_EVENT_TYPE_LABEL_AREA = 2
};

/*
 * Defines health status for namespace related metadata
 */
enum ns_health_result
{
	NAMESPACE_HEALTH_RESULT_OK = 0,
	NAMESPACE_HEALTH_RESULT_MISSING,
	NAMESPACE_HEALTH_RESULT_MISSING_LABEL,
	NAMESPACE_HEALTH_RESULT_CORRUPT_INTERLEAVE_SET,
	NAMESPACE_HEALTH_RESULT_INCONSISTENT_LABELS,
	NAMESPACE_HEALTH_RESULT_INVALID_BLOCK_SIZE,
	NAMESPACE_HEALTH_RESULT_CORRUPT_BTT_METADATA
};

/*
 * Defines health status for label area related metadata
 */
enum label_area_health_result
{
	LABEL_AREA_HEALTH_RESULT_OK = 0,
	LABEL_AREA_HEALTH_RESULT_MISSING_PCD,
	LABEL_AREA_HEALTH_RESULT_MISSING_VALID_INDEX_BLOCK,
	LABEL_AREA_HEALTH_RESULT_INSUFFICIENT_PERSISTENT_MEMORY,
	LABEL_AREA_HEALTH_RESULT_LABELS_OVERLAP
};

/*
 * ------------------------------------------------------------------------------------------------
 * Structures
 * ------------------------------------------------------------------------------------------------
 */
/*
 * Feature flags for the driver
 * Indicate whether a given feature is enabled or disabled by the driver.
 */
struct driver_feature_flags
{
	NVM_UINT32 get_platform_capabilities : 1;
	NVM_UINT32 get_topology : 1;
	NVM_UINT32 get_interleave : 1;
	NVM_UINT32 get_dimm_detail : 1;
	NVM_UINT32 get_namespaces : 1;
	NVM_UINT32 get_namespace_detail : 1;
	NVM_UINT32 get_address_scrub_data : 1;
	NVM_UINT32 get_platform_config_data : 1;
	NVM_UINT32 get_boot_status : 1;
	NVM_UINT32 get_power_data : 1;
	NVM_UINT32 get_security_state : 1;
	NVM_UINT32 get_log_page : 1;
	NVM_UINT32 get_features : 1;
	NVM_UINT32 set_features : 1;
	NVM_UINT32 create_namespace : 1;
	NVM_UINT32 rename_namespace : 1;
	NVM_UINT32 grow_namespace : 1;
	NVM_UINT32 shrink_namespace : 1;
	NVM_UINT32 delete_namespace : 1;
	NVM_UINT32 enable_namespace : 1;
	NVM_UINT32 disable_namespace : 1;
	NVM_UINT32 set_security_state : 1;
	NVM_UINT32 enable_logging : 1;
	NVM_UINT32 run_diagnostic : 1;
	NVM_UINT32 set_platform_config : 1;
	NVM_UINT32 passthrough : 1;
	NVM_UINT32 start_address_scrub : 1;
	NVM_UINT32 app_direct_mode : 1;
	NVM_UINT32 storage_mode : 1;
};

/*
 * Capabilities of the driver
 */
struct nvm_driver_capabilities
{
	NVM_UINT32 block_sizes[MAX_NUMBER_OF_BLOCK_SIZES]; // in bytes
	NVM_UINT32 num_block_sizes;
	NVM_UINT64 min_namespace_size; // in bytes
	NVM_BOOL namespace_memory_page_allocation_capable;
	struct driver_feature_flags features;
};

/*
 * Describes the system-level view of a physical memory module's properties.
 */
struct nvm_topology {
	NVM_NFIT_DEVICE_HANDLE device_handle;
	NVM_UINT16 id; /* The SMBIOS physical id of the memory device */
	NVM_UINT16 vendor_id; /* The vendor identifier */
	NVM_UINT16 device_id; /* The device identifier */
	NVM_UINT16 revision_id; /* The revision identifier */

	NVM_UINT16 subsystem_vendor_id;		// vendor identifier of the AEP DIMM non-volatile
										// memory subsystem controller
	NVM_UINT16 subsystem_device_id;		// device identifier of the AEP DIMM non-volatile
										// memory subsystem controller
	NVM_UINT16 subsystem_revision_id; 	// revision identifier of the AEP DIMM non-volatile
										// memory subsystem controller
	NVM_BOOL manufacturing_info_valid;	// manufacturing location and date validity
	NVM_UINT8 manufacturing_location;	// AEP DIMM manufacturing location assigned by vendor
										// only valid if manufacturing_info_valid=1
	NVM_UINT16 manufacturing_date;		// Date the AEP DIMM was manufactured, assigned by vendor
										// only valid if manufacturing_info_valid=1
	NVM_SERIAL_NUMBER serial_number;	// The serial number assigned by the vendor

	NVM_UINT16 state_flags;				// Device flags from the NFIT

	NVM_UINT16 fmt_interface_codes[NVM_MAX_IFCS_PER_DIMM]; /* The device type(s) from NFIT */
};

/*
 * Detailed information about a specific DIMM including information from the
 *  SMBIOS Type 17 tables
 */
struct nvm_details {
	NVM_UINT16 id; // SMBIOS handle
	NVM_UINT8 type; // SMBIOS memory type
	NVM_UINT32 type_detail_bits; // SMBIOS memory type detail bitfield
	NVM_UINT16 form_factor; /* DIMM Form Factor */
	/* Width in bits used to store user data */
	NVM_UINT64 data_width;
	NVM_UINT64 total_width; /* Width in bits for data and ECC */
	NVM_UINT64 size; //!< raw size reported by SMBIOS in bytes
	NVM_UINT64 speed; /* Speed in MHz */
	char part_number[NVM_PART_NUM_LEN]; /* DIMM part number */
	/* Socket or board pos */
	char device_locator[NVM_DEVICE_LOCATOR_LEN];
	/* Bank label */
	char bank_label[NVM_BANK_LABEL_LEN];
	char manufacturer[NVM_MANUFACTURERSTR_LEN]; // SMBIOS manufacturer string
};



/*
 * Interleave set information
 */
struct nvm_interleave_set
{
	NVM_UINT8 id; // Unique identifier from the NFIT
	NVM_UINT8 socket_id; // The socket where the interleave set resides
	NVM_UINT64 size; // the size of the interleave set in bytes
	NVM_UINT64 available_size; // the size of the interleave set in bytes
	NVM_UINT64 attributes;
	NVM_UINT8 dimm_count; // The number of dimm in the interleave set
	// NFIT handles of the dimms in the interleave set
	NVM_UINT32 dimms[NVM_MAX_DEVICES_PER_SOCKET];
	NVM_UINT64 dimm_region_pdas[NVM_MAX_DEVICES_PER_SOCKET];
	NVM_UINT64 dimm_region_offsets[NVM_MAX_DEVICES_PER_SOCKET];
	NVM_UINT64 dimm_sizes[NVM_MAX_DEVICES_PER_SOCKET];
	NVM_UINT32 set_index; // Unique identifier from the PCD (only used by sim adapter)
	NVM_UINT64 cookie_v1_1; // v1.1 cookie
	NVM_UINT64 cookie_v1_2; // v1.2 cookie
};


/*
 * A lightweight description of a namespace.
 */
struct nvm_namespace_discovery
{
	NVM_UID namespace_uid; // Unique identifier of the namespace
	char friendly_name[NVM_NAMESPACE_NAME_LEN]; // Human assigned name of the namespace
};
/*
 * Detailed namespace information
 */
struct nvm_namespace_details
{
	struct nvm_namespace_discovery discovery; // Discovery information
	NVM_UINT32 block_size; // The size of a block in bytes
	NVM_UINT64 block_count; // The number of blocks in the namespace
	enum namespace_type type; // The type of namespace
	enum namespace_health health; // Health of the underlying NVM-DIMMs
	enum namespace_enable_state enabled; // Exposure to OS
	NVM_BOOL btt; // optimized for speed
	union
	{
		NVM_NFIT_DEVICE_HANDLE device_handle; // Used when creating a Storage Namespace
		NVM_UINT32 interleave_setid; // Used when creating an App Direct Namespace
	} namespace_creation_id; // the identifier used by the driver when creating a Namespace
	enum namespace_memory_page_allocation memory_page_allocation;
	NVM_UINT16 nlabels;
	NVM_UINT32 label_sum;
};

/*
 * Caller specified settings for creating a new namespace.
 */
struct nvm_namespace_create_settings
{
	char friendly_name[NVM_NAMESPACE_NAME_LEN]; // User supplied friendly name.
	NVM_UINT16 block_size; // Block size in bytes.
	NVM_UINT64 block_count; // The number of blocks.
	enum namespace_type type; // The type of namespace.
	enum namespace_enable_state enabled; // If the namespace is exposed to OS after creation.
	NVM_BOOL btt; // optimized for speed
	union
	{
		NVM_NFIT_DEVICE_HANDLE device_handle; // Used when creating a Storage Namespace
		NVM_UINT32 interleave_setid; // Used when creating a App Direct Namespace
	} namespace_creation_id; // the identifier used by the driver when creating a Namespace
	enum namespace_memory_page_allocation memory_page_allocation;
};

/*
 * Caller specified settings for modifying a namespace
 */
struct nvm_namespace_modify_settings
{
	char friendly_name[NVM_NAMESPACE_NAME_LEN]; // User supplied friendly name.
	NVM_UINT64 block_count; // The number of blocks.
	enum namespace_enable_state enabled; // If the namespace is exposed to OS
};

/*
 * Result for a namespace metadata check
 */
struct namespace_health_event
{
	enum ns_health_result health_flag;
	NVM_UID namespace_uid;
};

/*
 * Result for a label area metadata check
 */
struct label_area_health_event
{
	enum label_area_health_result health_flag;
	NVM_UINT32 device_handle;
};

/*
 * Result of a driver metadata diagnostic check
 */
struct health_event
{
	enum driver_diagnostic_health_event_type event_type;
	union
	{
		struct namespace_health_event namespace_event;
		struct label_area_health_event label_area_event;
	} health;
};

#endif /* ADAPTER_TYPES_H_ */
