#pragma once

#include <webgpu/webgpu.hpp>
#include <memory>

class Device
{
public:
	Device();
	~Device();

	bool init(WGPUAdapter adapter);

private:
	WGPUDevice requestDeviceSync(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor);

private:
	WGPUDevice device_;
};

using DevicePtr = std::shared_ptr<Device>;