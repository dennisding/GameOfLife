
#include "wrender_pass.hpp"
//
//#include "wdevice.hpp"
//
//RenderPass::RenderPass(Device* device) 
//	: device_(device), command_encoder_(nullptr), render_pass_encoder_(nullptr)
//{
//}
//
//RenderPass::~RenderPass()
//{
//	release();
//}
//
//void RenderPass::begin(TexturePtr texture)
//{
//	command_encoder_ = device_->create_command_encoder();
//
//	WGPURenderPassDescriptor render_pass_desc = {};
//	WGPURenderPassColorAttachment color_attachment = {};
//
//	// setup render pass
//	render_pass_desc.nextInChain = nullptr;
//	render_pass_desc.colorAttachmentCount = 1;
//	render_pass_desc.colorAttachments = &color_attachment;
//	render_pass_desc.depthStencilAttachment = nullptr;
//	render_pass_desc.timestampWrites = nullptr;
//
//	// setup color attachment
//	color_attachment.view = texture->get_texture_view();
//	color_attachment.resolveTarget = nullptr;
//	color_attachment.loadOp = WGPULoadOp_Clear;
//	color_attachment.storeOp = WGPUStoreOp_Store;
//	color_attachment.clearValue = WGPUColor{ 0.1, 1.0, 0.2, 1.0 };
//
//	render_pass_encoder_ = wgpuCommandEncoderBeginRenderPass(command_encoder_, &render_pass_desc);
//}
//
//void RenderPass::end()
//{
//	wgpuRenderPassEncoderEnd(render_pass_encoder_);
//}
//
//void RenderPass::set_pipe_line(PipeLinePtr pipe_line)
//{
//	wgpuRenderPassEncoderSetPipeline(render_pass_encoder_, pipe_line->pipe_line_);
//}
//
//void RenderPass::draw(int vertex, int instance, int first_vertex, int first_instance)
//{
//	wgpuRenderPassEncoderDraw(render_pass_encoder_, vertex, instance, first_vertex, first_instance);
//}
//
//void RenderPass::release()
//{
//	if (command_encoder_) {
//		wgpuCommandEncoderRelease(command_encoder_);
//		command_encoder_ = nullptr;
//	}
//	if (render_pass_encoder_) {
//		wgpuRenderPassEncoderRelease(render_pass_encoder_);
//		render_pass_encoder_ = nullptr;
//	}
//}
