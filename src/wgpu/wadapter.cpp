
#include "wadapter.hpp"

Adapter::Adapter() : instance_(nullptr), adapter_(nullptr)
{
	// create the webgup instance
}

Adapter::~Adapter()
{

}

bool Adapter::init()
{
	WGPUInstanceDescriptor desc = {};
	desc.nextInChain = nullptr;

	instance_ = wgpuCreateInstance(&desc);
    if (!instance_) {
        return false;
    }

    if (!request_adapter()) {
        return false;
    }

    device_ = std::make_shared<Device>();
    if (!device_->init(adapter_)) {
        return false;
    }

    return true;
}

bool Adapter::request_adapter()
{
    struct UserData {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    };
    UserData user_data;

    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const* message, void* pUserData) {
        UserData& user_data = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestAdapterStatus_Success) {
            user_data.adapter = adapter;
        }
        else {
            std::cout << "Could not get WebGPU adapter: " << message << std::endl;
        }
        user_data.requestEnded = true;
        };

    WGPURequestAdapterOptions options = {};
    options.nextInChain = nullptr;
    wgpuInstanceRequestAdapter(
        instance_,
        &options,
        onAdapterRequestEnded,
        (void*)&user_data
    );

    adapter_ = user_data.adapter;

    return adapter_ != nullptr;
}