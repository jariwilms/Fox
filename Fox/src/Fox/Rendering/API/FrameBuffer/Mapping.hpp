#pragma once

#include "Fox/Rendering/API/FrameBuffer/FrameBuffer.hpp"

namespace fox::gfx::api
{
	static auto map_frame_buffer_texture_attachment      (api::Texture::Format      format)
	{
		switch (format)
		{
			case api::Texture::Format::D16_UNORM:
			case api::Texture::Format::D24_UNORM:
			case api::Texture::Format::D32_FLOAT:         return api::FrameBuffer::Attachment::Depth;

			case api::Texture::Format::D24_UNORM_S8_UINT:
			case api::Texture::Format::D32_FLOAT_S8_UINT: return api::FrameBuffer::Attachment::DepthStencil;

			case api::Texture::Format::S8_UINT:           return api::FrameBuffer::Attachment::Stencil;

			default:                                      return api::FrameBuffer::Attachment::Color;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
	static auto map_frame_buffer_cubemap_attachment      (api::Cubemap::Format      format)
	{
		switch (format)
		{
			case api::Cubemap::Format::D16_UNORM:
			case api::Cubemap::Format::D24_UNORM:
			case api::Cubemap::Format::D32_FLOAT:         return api::FrameBuffer::Attachment::Depth;

			case api::Cubemap::Format::D24_UNORM_S8_UINT:
			case api::Cubemap::Format::D32_FLOAT_S8_UINT: return api::FrameBuffer::Attachment::DepthStencil;

			case api::Cubemap::Format::S8_UINT:           return api::FrameBuffer::Attachment::Stencil;

			default:                                      return api::FrameBuffer::Attachment::Color;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
	static auto map_frame_buffer_render_buffer_attachment(api::RenderBuffer::Format format)
	{
		switch (format)
		{
			case api::RenderBuffer::Format::D16_UNORM:
			case api::RenderBuffer::Format::D24_UNORM:
			case api::RenderBuffer::Format::D32_FLOAT:         return api::FrameBuffer::Attachment::Depth;

			case api::RenderBuffer::Format::D24_UNORM_S8_UINT:
			case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return api::FrameBuffer::Attachment::DepthStencil;

			case api::RenderBuffer::Format::S8_UINT:           return api::FrameBuffer::Attachment::Stencil;

			default:                                           return api::FrameBuffer::Attachment::Color;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
}
