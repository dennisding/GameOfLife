
#include "wpipe_line_layout.hpp"

#include "wdevice.hpp"

PipeLineLayout::PipeLineLayout(Device* device)
	: device_(device), pipe_line_layout_(nullptr), bind_group_layout_(nullptr)
{
	create(device);
}

PipeLineLayout::~PipeLineLayout()
{
	release();
}

void PipeLineLayout::setDefault(WGPUBindGroupLayoutEntry& bindingLayout) 
{
	bindingLayout.buffer.nextInChain = nullptr;
	bindingLayout.buffer.type = WGPUBufferBindingType_Undefined;
	bindingLayout.buffer.hasDynamicOffset = false;

	bindingLayout.sampler.nextInChain = nullptr;
	bindingLayout.sampler.type = WGPUSamplerBindingType_Undefined;

	bindingLayout.storageTexture.nextInChain = nullptr;
	bindingLayout.storageTexture.access = WGPUStorageTextureAccess_Undefined;
	bindingLayout.storageTexture.format = WGPUTextureFormat_Undefined;
	bindingLayout.storageTexture.viewDimension = WGPUTextureViewDimension_Undefined;

	bindingLayout.texture.nextInChain = nullptr;
	bindingLayout.texture.multisampled = false;
	bindingLayout.texture.sampleType = WGPUTextureSampleType_Undefined;
	bindingLayout.texture.viewDimension = WGPUTextureViewDimension_Undefined;
}

void PipeLineLayout::create(Device* device)
{
	WGPUBindGroupLayoutEntry bindingLayout{};
	setDefault(bindingLayout);

	// The binding index as used in the @binding attribute in the shader
	bindingLayout.binding = 0;

	// The stage that needs to access this resource
	bindingLayout.visibility = WGPUShaderStage_Vertex;
	bindingLayout.visibility = WGPUShaderStage_Fragment;
	bindingLayout.buffer.type = WGPUBufferBindingType_Uniform;
	bindingLayout.buffer.minBindingSize = 4 * sizeof(float);

	WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc{};
	bindGroupLayoutDesc.nextInChain = nullptr;
	bindGroupLayoutDesc.entryCount = 1;
	bindGroupLayoutDesc.entries = &bindingLayout;
	bind_group_layout_ = wgpuDeviceCreateBindGroupLayout(device->device_, &bindGroupLayoutDesc);

	// Create the pipeline layout
	WGPUPipelineLayoutDescriptor layoutDesc{};
	layoutDesc.nextInChain = nullptr;
	layoutDesc.bindGroupLayoutCount = 1;
	layoutDesc.bindGroupLayouts = &bind_group_layout_;
	pipe_line_layout_ = wgpuDeviceCreatePipelineLayout(device->device_, &layoutDesc);
}

void PipeLineLayout::release()
{
	if (bind_group_layout_) {
		wgpuBindGroupLayoutRelease(bind_group_layout_);
		bind_group_layout_ = nullptr;
	}

	if (pipe_line_layout_) {
		wgpuPipelineLayoutRelease(pipe_line_layout_);
		pipe_line_layout_ = nullptr;
	}
}

BindGroupPtr PipeLineLayout::create_bind_group(size_t size)
{
	BindGroupPtr bind_group = std::make_shared<BindGroup>(device_);

	bind_group->create(this, size);

	return bind_group;
}