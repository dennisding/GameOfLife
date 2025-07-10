#pragma once

#include "wtexture.hpp"

#include <webgpu/webgpu.hpp>

#include <memory>
#include <vector>
#include <string>

class Device;

class CommandBuffer : std::enable_shared_from_this<CommandBuffer>
{
public:
	CommandBuffer(Device*);
	~CommandBuffer();

	void insert_debug_mark(const std::string& mark);

	void submit();
	void sync_submit();

private:
	void release();
	void release_commands();

private:
	Device* device_;
	WGPUCommandEncoder encoder_;
	std::vector<WGPUCommandBuffer> commands_;
};

class DebugCommand : std::enable_shared_from_this<DebugCommand>
{
public:

};

class RenderPassCommand : std::enable_shared_from_this<RenderPassCommand>
{
public:
	RenderPassCommand(Device* device);

	void begin(TexturePtr texture);
	void end();

	void submit();

public:
	Device* device_;
	WGPUCommandEncoder command_encoder_;
	WGPURenderPassEncoder render_pass_encoder_;
//	WGPUCommandBuffer command_;
};

using CommandBufferPtr = std::shared_ptr<CommandBuffer>;
using RenderPassCommandPtr = std::shared_ptr<RenderPassCommand>;
