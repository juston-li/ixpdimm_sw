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

/*
 * Add a layout warning if layout is not within acceptable deviation from the request
 */

#ifndef _core_LOGIC_LAYOUTSTEPCHECKREQUESTLAYOUTDEVIATION_H_
#define _core_LOGIC_LAYOUTSTEPCHECKREQUESTLAYOUTDEVIATION_H_

#include <nvm_types.h>
#include <core/memory_allocator/LayoutStep.h>

namespace core
{
namespace memory_allocator
{

class NVM_API LayoutStepCheckRequestLayoutDeviation : public LayoutStep
{
	public:
		LayoutStepCheckRequestLayoutDeviation();
		virtual ~LayoutStepCheckRequestLayoutDeviation();

		virtual void execute(const MemoryAllocationRequest &request, MemoryAllocationLayout &layout);

	protected:
		bool isMemoryCapacityLayoutAcceptable(
				const struct MemoryAllocationRequest& request,
				MemoryAllocationLayout& layout);

		bool isAppDirectCapacityLayoutAcceptable(
				const struct MemoryAllocationRequest& request,
				MemoryAllocationLayout& layout);

		NVM_UINT64 getNonReservedAppDirectCapacityGiBFromLayout(const struct MemoryAllocationRequest& request,
				const MemoryAllocationLayout& layout);

		double findPercentDeviation(NVM_UINT64 expectedValue, NVM_UINT64 observedValue, NVM_UINT64 totalCapacity);

		bool isLayoutDeviationWithinBounds(double percentDeviation);
};

} /* namespace memory_allocator */
} /* namespace core */

#endif /* _core_LOGIC_LAYOUTSTEPCHECKREQUESTLAYOUTDEVIATION_H_ */
