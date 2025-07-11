#pragma once

//#include <webgpu/webgpu.hpp>
//#include <memory>
//
//#include "wtexture.hpp"
//#include "wpipe_line.hpp"
//
//class Device;
//
//class RenderPass : std::enable_shared_from_this<RenderPass>
//{
//	using DevicePtr = std::shared_ptr<Device>;
//public:
//	RenderPass(Device* device);
//	~RenderPass();
//
//	void begin(TexturePtr texture);
//	void end();
//
//	void set_pipe_line(PipeLinePtr pipe_line);
//
//	void draw(int vertex, int count = 0, int first_vertex = 0, int first_instance = 0);
//
//private:
//	void release();
//
//private:
//	Device* device_;
//	WGPUCommandEncoder command_encoder_;
//	WGPURenderPassEncoder render_pass_encoder_;
//};
//
//using RenderPassPtr = std::shared_ptr<RenderPass>;