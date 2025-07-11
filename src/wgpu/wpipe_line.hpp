#pragma once

#include <webgpu/webgpu.hpp>
#include <memory>

class Device;

class PipeLine : std::enable_shared_from_this<PipeLine>
{
public:
	PipeLine(Device* device);
	~PipeLine();

public:
	// use in wgpu module
	Device* device_;
	WGPURenderPipeline pipe_line_;
};

using PipeLinePtr = std::shared_ptr<PipeLine>;