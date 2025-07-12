
#pragma once

#include "wbind_group.hpp"

#include <webgpu/webgpu.hpp>
#include <memory>

class Device;

class PipeLineLayout
{
public:
	PipeLineLayout(Device* device);
	~PipeLineLayout();

	BindGroupPtr create_bind_group(size_t size);

private:
	void create(Device* device);
	void release();
	void setDefault(WGPUBindGroupLayoutEntry& bindingLayout);

public:
	// use in wgpu
	Device* device_;
	WGPUPipelineLayout pipe_line_layout_;
	WGPUBindGroupLayout bind_group_layout_;
};

using PipeLineLayoutPtr = std::shared_ptr<PipeLineLayout>;
