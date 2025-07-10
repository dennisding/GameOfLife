
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
	//auto onQueueWorkDone = [](WGPUQueueWorkDoneStatus status, void* /* pUserData */) {
	//	std::cout << "Queued work finished with status: " << status << std::endl;
	//	};
	//wgpuQueueOnSubmittedWorkDone(queue, onQueueWorkDone, nullptr /* pUserData */);
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
	color_attachment.loadOp = WGPULoadOp_Clear;
	color_attachment.storeOp = WGPUStoreOp_Store;
	color_attachment.clearValue = WGPUColor{ 0.3, 0.3, 0.3, 1.0 };

	render_pass_encoder_ = wgpuCommandEncoderBeginRenderPass(command_encoder_, &render_pass_desc);
}

void RenderPassCommand::end()
{
	wgpuRenderPassEncoderEnd(render_pass_encoder_);
	wgpuRenderPassEncoderRelease(render_pass_encoder_);
	render_pass_encoder_ = nullptr;
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