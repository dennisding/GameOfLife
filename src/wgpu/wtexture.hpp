#pragma once

#include <webgpu/webgpu.hpp>

#include <memory>

class Texture
{
public:
	Texture();
	~Texture();

	void from_texture(WGPUTexture texture);
	void release();

public:
	// use in wgpu module
	WGPUTextureView get_texture_view();
	WGPUTextureFormat get_format();

private:
	WGPUTextureFormat format_;
	WGPUTextureView texture_view_;
};

using TexturePtr = std::shared_ptr<Texture>;