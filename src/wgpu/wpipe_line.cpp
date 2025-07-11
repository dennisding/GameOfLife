
#include "wpipe_line.hpp"
#include "wdevice.hpp"

static const char* shader_code = R"(
@vertex
fn vs_main(@location(0) in_vertex_position: vec2f) -> @builtin(position) vec4f {
	return vec4f(in_vertex_position, 0.0, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4f {
	return vec4f(0.0, 0.4, 1.0, 1.0);
}
)";

PipeLine::PipeLine(Device* device) : device_(device)
{
	// create the shader module
	WGPUShaderModuleDescriptor shaderDesc{};
	shaderDesc.hintCount = 0;
	shaderDesc.hints = nullptr;
	// shader code
	WGPUShaderModuleWGSLDescriptor shaderCodeDesc{};
	// Set the chained struct's header
	shaderCodeDesc.chain.next = nullptr;
	shaderCodeDesc.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
	// Connect the chain
	shaderDesc.nextInChain = &shaderCodeDesc.chain;
	// set the code
	shaderCodeDesc.code = shader_code;

	WGPUShaderModule shaderModule = wgpuDeviceCreateShaderModule(device_->device_, &shaderDesc);

	// positoin attribute
	WGPUVertexAttribute positionAttrib;
	positionAttrib.shaderLocation = 0;
	positionAttrib.format = WGPUVertexFormat_Float32x2;
	positionAttrib.offset = 0;

	// vertex buffer
	WGPUVertexBufferLayout vertexBufferLayout{};
	vertexBufferLayout.attributeCount = 1;
	vertexBufferLayout.attributes = &positionAttrib;
	vertexBufferLayout.arrayStride = 2 * sizeof(float);
	vertexBufferLayout.stepMode = WGPUVertexStepMode_Vertex;

	// creat the pipe line
	WGPURenderPipelineDescriptor pipe_line_desc;
	pipe_line_desc.nextInChain = nullptr;
	pipe_line_desc.label = "render pass";

	pipe_line_desc.vertex.nextInChain = nullptr;
	pipe_line_desc.vertex.bufferCount = 1;
	pipe_line_desc.vertex.buffers = &vertexBufferLayout;


	pipe_line_desc.vertex.module = shaderModule;
	pipe_line_desc.vertex.entryPoint = "vs_main";
	pipe_line_desc.vertex.constantCount = 0;
	pipe_line_desc.vertex.constants = nullptr;

	pipe_line_desc.primitive.nextInChain = nullptr;
	pipe_line_desc.primitive.topology = WGPUPrimitiveTopology_TriangleList;
	pipe_line_desc.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;
	pipe_line_desc.primitive.frontFace = WGPUFrontFace_CCW;
	pipe_line_desc.primitive.cullMode = WGPUCullMode_None;

	// blending
	WGPUBlendState blendState{};
	// blend color
	blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
	blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
	blendState.color.operation = WGPUBlendOperation_Add;
	// blend alpha
	blendState.alpha.srcFactor = WGPUBlendFactor_Zero;
	blendState.alpha.dstFactor = WGPUBlendFactor_One;
	blendState.alpha.operation = WGPUBlendOperation_Add;

	// color state
	WGPUColorTargetState colorTarget{};
	colorTarget.format = device_->surface_texture_->get_format();
	colorTarget.blend = &blendState;
	colorTarget.writeMask = WGPUColorWriteMask_All;

	WGPUFragmentState fragmentState{};
	fragmentState.module = shaderModule;
	fragmentState.entryPoint = "fs_main";
	fragmentState.constantCount = 0;
	fragmentState.constants = nullptr;
	fragmentState.targetCount = 1;
	fragmentState.targets = &colorTarget;
	pipe_line_desc.fragment = &fragmentState;

	pipe_line_desc.depthStencil = nullptr;

	pipe_line_desc.multisample.nextInChain = nullptr;
	pipe_line_desc.multisample.count = 1;
	pipe_line_desc.multisample.mask = ~0u;
	pipe_line_desc.multisample.alphaToCoverageEnabled = false;

	pipe_line_desc.layout = nullptr;

	pipe_line_ = wgpuDeviceCreateRenderPipeline(device_->device_, &pipe_line_desc);

	wgpuShaderModuleRelease(shaderModule);
}

PipeLine::~PipeLine()
{
	wgpuRenderPipelineRelease(pipe_line_);
	pipe_line_ = nullptr;
}