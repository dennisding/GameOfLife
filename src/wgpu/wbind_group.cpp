
#include "wbind_group.hpp"

#include "wdevice.hpp"
#include "wpipe_line_layout.hpp"

BindGroup::BindGroup(Device* device) : device_(device), bind_group_(nullptr)
{
	//WGPUBindGroupEntry binding{};
	//binding.nextInChain = nullptr;
	//// The index of the binding (the entries in bindGroupDesc can be in any order)
	//binding.binding = 0;
	//// The buffer it is actually bound to
	//binding.buffer = uniformBuffer;
	//// We can specify an offset within the buffer, so that a single buffer can hold
	//// multiple uniform blocks.
	//binding.offset = 0;
	//// And we specify again the size of the buffer.
	//binding.size = 4 * sizeof(float);

	//// A bind group contains one or multiple bindings
	//WGPUBindGroupDescriptor bindGroupDesc{};
	//bindGroupDesc.nextInChain = nullptr;
	//bindGroupDesc.layout = bindGroupLayout;
	//// There must be as many bindings as declared in the layout!
	//bindGroupDesc.entryCount = 1;
	//bindGroupDesc.entries = &binding;
	//bindGroup = wgpuDeviceCreateBindGroup(device, &bindGroupDesc);
}

BindGroup::~BindGroup()
{
	release();
}

void BindGroup::create(PipeLineLayout* layout, size_t size)
{
	buffer_ = device_->create_uniform_buffer(size);

	WGPUBindGroupEntry binding{};
	binding.nextInChain = nullptr;
	// The index of the binding (the entries in bindGroupDesc can be in any order)
	binding.binding = 0;
	// The buffer it is actually bound to
	binding.buffer = buffer_->buffer_;
	// We can specify an offset within the buffer, so that a single buffer can hold
	// multiple uniform blocks.
	binding.offset = 0;
	// And we specify again the size of the buffer.
	binding.size = 4 * sizeof(float);

	// A bind group contains one or multiple bindings
	WGPUBindGroupDescriptor bindGroupDesc{};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = layout->bind_group_layout_;
	// There must be as many bindings as declared in the layout!
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &binding;
	bind_group_ = wgpuDeviceCreateBindGroup(device_->device_, &bindGroupDesc);
}

void BindGroup::release()
{
	if (bind_group_) {
		wgpuBindGroupRelease(bind_group_);
		bind_group_ = nullptr;
	}
}