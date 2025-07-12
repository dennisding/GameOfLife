#pragma once

#include <webgpu/webgpu.hpp>
#include <memory>

class Device;

class Buffer : std::enable_shared_from_this<Buffer>
{
public:
	Buffer(Device* device);
	~Buffer();

	void create(size_t size);
	void create_uniform(size_t size);
	void write(size_t size, void* data);

private:
	void release();

public:
	// use in wgpu
	Device* device_;
	WGPUBuffer buffer_;
};

using BufferPtr = std::shared_ptr<Buffer>;
