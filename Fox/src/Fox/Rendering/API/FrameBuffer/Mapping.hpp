#pragma once

#include "Fox/Rendering/API/FrameBuffer/FrameBuffer.hpp"

namespace fox::gfx::api
{
	static constexpr FrameBuffer::Attachment map_frame_buffer_texture_attachment(Texture::Format format)
	{
		switch (format)
		{
			case Texture::Format::D16_UNORM:
			case Texture::Format::D24_UNORM:
			case Texture::Format::D32_FLOAT:         return FrameBuffer::Attachment::Depth;

			case Texture::Format::D24_UNORM_S8_UINT:
			case Texture::Format::D32_FLOAT_S8_UINT: return FrameBuffer::Attachment::DepthStencil;

			case Texture::Format::S8_UINT:           return FrameBuffer::Attachment::Stencil;

			default:                                 return FrameBuffer::Attachment::Color;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
	static constexpr FrameBuffer::Attachment map_frame_buffer_render_buffer_attachment(RenderBuffer::Format format)
	{
		switch (format)
		{
			case RenderBuffer::Format::D16_UNORM:
			case RenderBuffer::Format::D24_UNORM:
			case RenderBuffer::Format::D32_FLOAT:         return FrameBuffer::Attachment::Depth;

			case RenderBuffer::Format::D24_UNORM_S8_UINT:
			case RenderBuffer::Format::D32_FLOAT_S8_UINT: return FrameBuffer::Attachment::DepthStencil;

			case RenderBuffer::Format::S8_UINT:           return FrameBuffer::Attachment::Stencil;

			default:                                      return FrameBuffer::Attachment::Color;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
	static constexpr FrameBuffer::Attachment map_frame_buffer_cubemap_attachment(Cubemap::Format format)
	{
		switch (format)
		{
			case Cubemap::Format::D16_UNORM:
			case Cubemap::Format::D24_UNORM:
			case Cubemap::Format::D32_FLOAT:         return FrameBuffer::Attachment::Depth;

			case Cubemap::Format::D24_UNORM_S8_UINT:
			case Cubemap::Format::D32_FLOAT_S8_UINT: return FrameBuffer::Attachment::DepthStencil;

			case Cubemap::Format::S8_UINT:           return FrameBuffer::Attachment::Stencil;

			default:                                 return FrameBuffer::Attachment::Color;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
}
