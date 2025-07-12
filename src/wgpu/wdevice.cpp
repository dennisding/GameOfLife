
#include "wdevice.hpp"

#include "wtexture.hpp"
#include "wadapter.hpp"

#include <glfw3webgpu.h>

Device::Device(WGPUInstance instance, Adapter* adapter) 
    : instance_(instance), adapter_(adapter), 
    device_(nullptr), queue_(nullptr), surface_(nullptr)
{

}

Device::~Device()
{
    if (queue_) {
        wgpuQueueRelease(queue_);
        queue_ = nullptr;
    }
    if (device_) {
        wgpuDeviceRelease(device_);
        device_ = nullptr;
    }
}

bool Device::init(WGPUAdapter adapter)
{
    WGPURequiredLimits requiredLimits = adapter_->GetRequiredLimits();

    WGPUDeviceDescriptor device_desc = {};
    device_desc.nextInChain = nullptr;
    device_desc.label = "GameOfLife Device"; // anything works here, that's your call
    device_desc.requiredFeatureCount = 0; // we do not require any specific feature
    device_desc.requiredLimits = &requiredLimits;
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

    if (device_ == nullptr) {
        return false;
    }

    queue_ = wgpuDeviceGetQueue(device_);
    auto onQueueWorkDone = [](WGPUQueueWorkDoneStatus status, void* /* pUserData */) {
    	std::cout << "Queued work finished with status: " << status << std::endl;
    	};
    wgpuQueueOnSubmittedWorkDone(queue_, onQueueWorkDone, nullptr /* pUserData */);
    if (queue_ == nullptr) {
        return false;
    }

    return device_ != nullptr;
}

void Device::pre_tick()
{
    // create the new texture
    WGPUSurfaceTexture surface_texture;
    wgpuSurfaceGetCurrentTexture(surface_, &surface_texture);
    if (surface_texture.status != WGPUSurfaceGetCurrentTextureStatus_Success) {
        return;
    }

    surface_texture_ = std::make_shared<Texture>();
    surface_texture_->from_texture(surface_texture.texture);
}

void Device::tick()
{
}

void Device::post_tick()
{
    wgpuSurfacePresent(surface_);
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

    assert(userData.requestEnded);

    return userData.device;
}

RenderPassCommandPtr Device::create_render_pass_command()
{
    return std::make_shared<RenderPassCommand>(this);
}

BufferPtr Device::create_buffer(size_t size)
{
    BufferPtr buffer = std::make_shared<Buffer>(this);
    buffer->create(size);
    return buffer;
}

BufferPtr Device::create_uniform_buffer(size_t size)
{
    BufferPtr buffer = std::make_shared<Buffer>(this);
    buffer->create_uniform(size);

    return buffer;
}

WGPUCommandEncoder Device::create_command_encoder()
{
    WGPUCommandEncoderDescriptor encoder_desc = {};
    encoder_desc.nextInChain = nullptr;
    encoder_desc.label = "command encoder";

    return wgpuDeviceCreateCommandEncoder(device_, &encoder_desc);
}

PipeLinePtr Device::create_render_pipe_line(PipeLineLayoutPtr pipe_layout)
{
    auto pipe_line = std::make_shared<PipeLine>(this);
    pipe_line->create(this, pipe_layout);
    return pipe_line;
}

PipeLineLayoutPtr Device::create_pipe_line_layout()
{
    return std::make_shared<PipeLineLayout>(this);
}

bool Device::config_surface(GLFWwindow* window)
{
    if (surface_ != nullptr) {
        wgpuSurfaceRelease(surface_);
    }

    surface_ = glfwGetWGPUSurface(instance_, window);
    WGPUSurfaceConfiguration config = {};
    config.nextInChain = nullptr;

    int width = 1024;
    int height = 768;
    glfwGetWindowSize(window, &width, &height);
    config.width = width;
    config.height = height;

    config.format = wgpuSurfaceGetPreferredFormat(surface_, adapter_->adapter_);;
    config.viewFormatCount = 0;
    config.viewFormats = nullptr;

    config.usage = WGPUTextureUsage_RenderAttachment;
    config.device = device_;

    config.presentMode = WGPUPresentMode_Fifo;
    config.alphaMode = WGPUCompositeAlphaMode_Auto;
    
    wgpuSurfaceConfigure(surface_, &config);

    return true;
}

void Device::submit_commands(size_t size, WGPUCommandBuffer* commands)
{
    wgpuQueueSubmit(queue_, size, commands);
}

TexturePtr Device::get_surface_texture()
{
    return surface_texture_;
}
