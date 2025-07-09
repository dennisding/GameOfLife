
#include "wdevice.hpp"

Device::Device()
{

}

Device::~Device()
{

}

bool Device::init(WGPUAdapter adapter)
{
    WGPUDeviceDescriptor device_desc = {};
    device_desc.nextInChain = nullptr;
    device_desc.label = "GameOfLife Device"; // anything works here, that's your call
    device_desc.requiredFeatureCount = 0; // we do not require any specific feature
    device_desc.requiredLimits = nullptr; // we do not require any specific limit
    device_desc.defaultQueue.nextInChain = nullptr;
    device_desc.defaultQueue.label = "The default queue";
    device_desc.deviceLostCallback = nullptr;
    device_ = requestDeviceSync(adapter, &device_desc);

    auto on_device_error = [](WGPUErrorType type, char const* message, void* /* pUserData */) {
        std::cout << "Uncaptured device error: type " << type;
        if (message) std::cout << " (" << message << ")";
        std::cout << std::endl;
        };
    wgpuDeviceSetUncapturedErrorCallback(device_, on_device_error, nullptr /* pUserData */);

    return device_ != nullptr;
}

WGPUDevice Device::requestDeviceSync(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor)
{
    struct UserData {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const* message, void* pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestDeviceStatus_Success) {
            userData.device = device;
        }
        else {
            std::cout << "Could not get WebGPU device: " << message << std::endl;
        }
        userData.requestEnded = true;
        };

    wgpuAdapterRequestDevice(
        adapter,
        descriptor,
        onDeviceRequestEnded,
        (void*)&userData
    );

#ifdef __EMSCRIPTEN__
    while (!userData.requestEnded) {
        emscripten_sleep(100);
    }
#endif // __EMSCRIPTEN__

    assert(userData.requestEnded);

    return userData.device;
}