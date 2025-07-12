
#include "wcommand_buffer.hpp"

#include "wdevice.hpp"

CommandBuffer::CommandBuffer(Device* device) 
	: device_(device), encoder_(nullptr)
{

}

CommandBuffer::~CommandBuffer()
{
	for (auto command : commands_) {
		wgpuCommandBufferRelease(command);
	}
}

void CommandBuffer::insert_debug_mark(const std::string& mark)
{
	wgpuCommandEncoderInsertDebugMarker(encoder_, mark.c_str());

	// create the command
	WGPUCommandBufferDescriptor command_buffer_descriptor = {};
	command_buffer_descriptor.nextInChain = nullptr;
	command_buffer_descriptor.label = "Command buffer";
	WGPUCommandBuffer command = wgpuCommandEncoderFinish(encoder_, &command_buffer_descriptor);

	commands_.push_back(command);
}

void CommandBuffer::submit()
{
	device_->submit_commands(commands_.size(), commands_.data());
}

void CommandBuffer::sync_submit()
{
}

void CommandBuffer::release()
{
	if (encoder_) {
		wgpuCommandEncoderRelease(encoder_);
		encoder_ = nullptr;
	}
}

void CommandBuffer::release_commands()
{
	for (auto command : commands_) {
		wgpuCommandBufferRelease(command);
	}
}

RenderPassCommand::RenderPassCommand(Device* device) 
	: device_(device), render_pass_encoder_(nullptr)
{
	command_encoder_ = device_->create_command_encoder();
}

RenderPassCommand::~RenderPassCommand()
{

}

void RenderPassCommand::begin(TexturePtr texture)
{
	WGPURenderPassDescriptor render_pass_desc = {};
	WGPURenderPassColorAttachment color_attachment = {};

	// setup render pass
	render_pass_desc.nextInChain = nullptr;
	render_pass_desc.colorAttachmentCount = 1;
	render_pass_desc.colorAttachments = &color_attachment;
	render_pass_desc.depthStencilAttachment = nullptr;
	render_pass_desc.timestampWrites = nullptr;

	// setup color attachment
	color_attachment.view = texture->get_texture_view();
	color_attachment.resolveTarget = nullptr;
	color_attachment.loadOp = WGPULoadOp_Load;
//	color_attachment.loadOp = WGPULoadOp_Clear;
	color_attachment.storeOp = WGPUStoreOp_Store;
	color_attachment.clearValue = WGPUColor{ 0.83, 0.92, 0.94, 1.0 };

	render_pass_encoder_ = wgpuCommandEncoderBeginRenderPass(command_encoder_, &render_pass_desc);
}

void RenderPassCommand::end()
{
	wgpuRenderPassEncoderEnd(render_pass_encoder_);
	wgpuRenderPassEncoderRelease(render_pass_encoder_);
	render_pass_encoder_ = nullptr;
}

void RenderPassCommand::set_pipe_line(PipeLinePtr pipe_line)
{
	wgpuRenderPassEncoderSetPipeline(render_pass_encoder_, pipe_line->pipe_line_);
}

void RenderPassCommand::set_vertex_buffer(size_t slot, BufferPtr buffer)
{
	size_t size = wgpuBufferGetSize(buffer->buffer_);
	wgpuRenderPassEncoderSetVertexBuffer(render_pass_encoder_, uint32_t(slot), buffer->buffer_, 0, size);
}

void RenderPassCommand::set_bind_group(size_t slot, BindGroupPtr bind_group)
{
	wgpuRenderPassEncoderSetBindGroup(render_pass_encoder_, 0, bind_group->bind_group_, 0, nullptr);
}

void RenderPassCommand::draw(size_t vertex, size_t instance, size_t first_vertex, size_t first_instance)
{
	wgpuRenderPassEncoderDraw(render_pass_encoder_, 
		(uint32_t)vertex, (uint32_t)instance, (uint32_t)first_vertex, (uint32_t)first_instance);
}

void RenderPassCommand::submit()
{
	WGPUCommandBufferDescriptor command_buffer_desc = {};
	command_buffer_desc.nextInChain = nullptr;
	command_buffer_desc.label = "render pass command";
	WGPUCommandBuffer command = wgpuCommandEncoderFinish(command_encoder_, &command_buffer_desc);
	wgpuCommandEncoderRelease(command_encoder_); // release encoder after it's finished
	command_encoder_ = nullptr;

	device_->submit_commands(1, &command);
	wgpuCommandBufferRelease(command);
}