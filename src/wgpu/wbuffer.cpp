
#include "wbuffer.hpp"

#include "wdevice.hpp"

Buffer::Buffer(Device* device) : device_(device), buffer_(nullptr)
{
}

Buffer::~Buffer()
{
	release();
}

void Buffer::create(size_t size)
{
	release();

	// 
	WGPUBufferDescriptor bufferDesc = {};
	bufferDesc.nextInChain = nullptr;
	bufferDesc.label = "data buffer";
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	bufferDesc.size = size;
	bufferDesc.mappedAtCreation = false;
	buffer_ = wgpuDeviceCreateBuffer(device_->device_, &bufferDesc);
}

void Buffer::write(size_t size, void* data)
{
	wgpuQueueWriteBuffer(device_->queue_, buffer_, 0, data, size);
}

void Buffer::release()
{
	if (buffer_) {
		wgpuBufferRelease(buffer_);
		buffer_ = nullptr;
	}
}