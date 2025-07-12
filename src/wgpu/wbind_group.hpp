#pragma once

#include "wbuffer.hpp"

#include <webgpu/webgpu.hpp>
#include <memory>

class Device;
class PipeLineLayout;

class BindGroup
{
public:
	BindGroup(Device* device);
	~BindGroup();

	void create(PipeLineLayout* layout, size_t size);

private:
	void release();

public:
	Device* device_;
	BufferPtr buffer_;
	WGPUBindGroup bind_group_;
};

using BindGroupPtr = std::shared_ptr<BindGroup>;
