#pragma once

#include "wtexture.hpp"
#include "wrender_pass.hpp"
#include "wcommand_buffer.hpp"
#include "wpipe_line.hpp"
#include "wbuffer.hpp"
#include "wpipe_line_layout.hpp"

#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu.hpp>
#include <GLFW/glfw3.h>

#include <memory>

class Adapter;

class Device : std::enable_shared_from_this<Device>
{
public:
	Device(WGPUInstance instance, Adapter* adapter);
	~Device();

	bool init(WGPUAdapter adapter);
	void pre_tick();
	void tick();
	void post_tick();

//	CommandBufferPtr create_command_buffer();
	RenderPassCommandPtr create_render_pass_command();
	WGPUCommandEncoder create_command_encoder();

	// pipe line relative
	PipeLinePtr create_render_pipe_line(PipeLineLayoutPtr layout);
	PipeLineLayoutPtr create_pipe_line_layout();

	// buffer relative
	BufferPtr create_buffer(size_t size);
	BufferPtr create_uniform_buffer(size_t size);

	bool config_surface(GLFWwindow* window);

public:
	// use in wgpu module
	void submit_commands(size_t size, WGPUCommandBuffer* commands);
	TexturePtr get_surface_texture();

private:
	WGPUDevice requestDeviceSync(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor);

public:
	// use in mgpu
	WGPUInstance instance_;
//	WGPUAdapter adapter_;
	Adapter* adapter_;
	WGPUDevice device_;
	WGPUQueue queue_;
	WGPUSurface surface_;

	TexturePtr surface_texture_;
};

using DevicePtr = std::shared_ptr<Device>;