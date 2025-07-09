#pragma once

#include <webgpu/webgpu.hpp>
#include <memory>

#include "wdevice.hpp"

class Adapter
{
public:
	Adapter();
	~Adapter();

	bool init();

private:
	bool request_adapter();

private:
	WGPUInstance instance_;
	WGPUAdapter adapter_;

	DevicePtr device_;
};

using AdapterPtr = std::shared_ptr<Adapter>;