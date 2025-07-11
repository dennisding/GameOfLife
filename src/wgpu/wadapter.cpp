
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

    device_ = std::make_shared<Device>(instance_, this);
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

void Adapter::set_default_limits(WGPULimits& limits) const 
{
    limits.maxTextureDimension1D = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxTextureDimension2D = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxTextureDimension3D = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxTextureDimension1D = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxTextureDimension2D = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxTextureDimension3D = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxTextureArrayLayers = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxBindGroups = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxBindGroupsPlusVertexBuffers = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxBindingsPerBindGroup = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxDynamicUniformBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxDynamicStorageBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxSampledTexturesPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxSamplersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxStorageBuffersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxStorageTexturesPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxUniformBuffersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxUniformBufferBindingSize = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxStorageBufferBindingSize = WGPU_LIMIT_U32_UNDEFINED;
    limits.minUniformBufferOffsetAlignment = WGPU_LIMIT_U32_UNDEFINED;
    limits.minStorageBufferOffsetAlignment = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxVertexBuffers = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxBufferSize = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxVertexAttributes = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxVertexBufferArrayStride = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxInterStageShaderComponents = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxInterStageShaderVariables = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxColorAttachments = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxColorAttachmentBytesPerSample = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxComputeWorkgroupStorageSize = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxComputeInvocationsPerWorkgroup = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxComputeWorkgroupSizeX = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxComputeWorkgroupSizeY = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxComputeWorkgroupSizeZ = WGPU_LIMIT_U32_UNDEFINED;
    limits.maxComputeWorkgroupsPerDimension = WGPU_LIMIT_U32_UNDEFINED;
}

WGPURequiredLimits Adapter::GetRequiredLimits() const {
    // Get adapter supported limits, in case we need them
    WGPUSupportedLimits supportedLimits;
    supportedLimits.nextInChain = nullptr;
    wgpuAdapterGetLimits(adapter_, &supportedLimits);

    WGPURequiredLimits requiredLimits{};
    requiredLimits.nextInChain = nullptr;
//    set_default_limits(requiredLimits.limits);
    requiredLimits.limits = supportedLimits.limits;

    //// We use at most 1 vertex attribute for now
    //requiredLimits.limits.maxVertexAttributes = 1;
    //// We should also tell that we use 1 vertex buffers
    //requiredLimits.limits.maxVertexBuffers = 1;
    //// Maximum size of a buffer is 6 vertices of 2 float each
    //requiredLimits.limits.maxBufferSize = 6 * 2 * sizeof(float);
    //// Maximum stride between 2 consecutive vertices in the vertex buffer
    //requiredLimits.limits.maxVertexBufferArrayStride = 2 * sizeof(float);

    // [...] Other device limits

    return requiredLimits;
}