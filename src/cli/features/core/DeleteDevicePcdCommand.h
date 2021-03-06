/*
 * Copyright (c) 2017 Intel Corporation
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

#ifndef CR_MGMT_DELETEDEVICEPCDCOMMAND_H
#define CR_MGMT_DELETEDEVICEPCDCOMMAND_H

#include <cli/features/core/framework/CommandBase.h>
#include <cli/features/core/framework/YesNoPrompt.h>
#include <libinvm-cli/CommandSpec.h>
#include <core/device/DeviceService.h>
#include <core/StringList.h>

namespace cli
{
namespace nvmcli
{

static const std::string DELETEDEVICEPCD_MSG = "Clear LSA in Platform Configuration Data On Device ";

class NVM_API DeleteDevicePcdCommand : public framework::CommandBase
{
	public:
		DeleteDevicePcdCommand(
				core::device::DeviceService &service = core::device::DeviceService::getService(),
				core::NvmLibrary &nvmLib = core::NvmLibrary::getNvmLibrary());

		virtual ~DeleteDevicePcdCommand();

		static framework::CommandSpec getCommandSpec(int id);

		framework::ResultBase *execute(const framework::ParsedCommand &parsedCommand);

		/*!
		 * Prompt User DeletePCD message and read user input.
		 * @return
		 *				true if user answered "Y" or "y"
		 *				false otherwise
		 */
		static bool promptUserToDeletePCD(core::device::Device &device);

		/*!
		 * Method that can be overridden for testing purposes.
		 * Defaults to just calling promptUserToDeletePCD above.
		 */
		bool (*m_checkPromptResponseToDeletePCD)(core::device::Device &device);

	private:

		core::device::DeviceService &m_service;

		framework::ResultBase *m_pResult;

		core::StringList m_dimmIds;

		core::device::DeviceCollection m_devices;

		core::NvmLibrary &m_nvmLib;

		bool dimmIdsAreValid();

		void filterDevicesOnDimmIds();

		void deleteDevicesPcdLsa();

		bool hasForceOption();
};

}
}

#endif /* CR_MGMT_DELETEDEVICEPCDCOMMAND_H */
