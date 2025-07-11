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

	inline DevicePtr get_device() { return device_; }
	WGPURequiredLimits GetRequiredLimits() const;

private:
	bool request_adapter();
	void set_default_limits(WGPULimits& limits) const;

public:
	// use in wgpu
	WGPUInstance instance_;
	WGPUAdapter adapter_;

	DevicePtr device_;
};

using AdapterPtr = std::shared_ptr<Adapter>;