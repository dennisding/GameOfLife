
#include "wtexture.hpp"

Texture::Texture() : texture_view_(nullptr)
{

}

Texture::~Texture()
{
	release();
}

void Texture::from_texture(WGPUTexture texture)
{
	release();

	// create the new texture view
	WGPUTextureViewDescriptor view_description;
	view_description.nextInChain = nullptr;
	view_description.label = "Surface texture view";
	view_description.format = wgpuTextureGetFormat(texture);
	view_description.dimension = WGPUTextureViewDimension_2D;
	view_description.baseMipLevel = 0;
	view_description.mipLevelCount = 1;
	view_description.baseArrayLayer = 0;
	view_description.arrayLayerCount = 1;
	view_description.aspect = WGPUTextureAspect_All;
	texture_view_ = wgpuTextureCreateView(texture, &view_description);
}

void Texture::release()
{
	if (texture_view_) {
		wgpuTextureViewRelease(texture_view_);
		texture_view_ = nullptr;
	}
}

WGPUTextureView Texture::get_texture_view()
{
	return texture_view_;
}
