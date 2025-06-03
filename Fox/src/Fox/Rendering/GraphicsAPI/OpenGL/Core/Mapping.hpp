#pragma once

#include "glad/gl.h"
#include "glfw/glfw3.h"

#include "Fox/Rendering/API/Buffer/Buffer.hpp"
#include "Fox/Rendering/API/Buffer/DataType.hpp"
#include "Fox/Rendering/API/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/API/Query/Query.hpp"
#include "Fox/Rendering/API/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/API/RenderState/RenderState.hpp"
#include "Fox/Rendering/API/Shader/Pipeline.hpp"
#include "Fox/Rendering/API/Shader/Shader.hpp"
#include "Fox/Rendering/API/Texture/Cubemap.hpp"
#include "Fox/Rendering/API/Texture/Texture.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Core/Types.hpp"

namespace fox::gfx::api::gl
{
    static auto map_type                                 (api::Type type)
    {
        if (type == api::Type::Byte           ) return glf::VertexArray::Attribute::Type::Byte;
        if (type == api::Type::UnsignedByte   ) return glf::VertexArray::Attribute::Type::UnsignedByte;
        if (type == api::Type::Short          ) return glf::VertexArray::Attribute::Type::Short;
        if (type == api::Type::UnsignedShort  ) return glf::VertexArray::Attribute::Type::UnsignedShort;
        if (type == api::Type::Integer        ) return glf::VertexArray::Attribute::Type::Integer;
        if (type == api::Type::UnsignedInteger) return glf::VertexArray::Attribute::Type::UnsignedInteger;
        if (type == api::Type::Float          ) return glf::VertexArray::Attribute::Type::Float;
        if (type == api::Type::Double         ) return glf::VertexArray::Attribute::Type::Double;

        throw std::invalid_argument{ "Invalid Data Type!" };
    }

    static auto map_texture_format_base                  (api::Texture::Format format)
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM    :
            case api::Texture::Format::R16_UNORM   :
            case api::Texture::Format::R8_SNORM    :
            case api::Texture::Format::R16_SNORM   :
            case api::Texture::Format::R16_FLOAT   :
            case api::Texture::Format::R32_FLOAT   : return glf::Texture::BaseFormat::R;
            
            case api::Texture::Format::RG8_UNORM   :
            case api::Texture::Format::RG16_UNORM  :
            case api::Texture::Format::RG8_SNORM   :
            case api::Texture::Format::RG16_SNORM  :
            case api::Texture::Format::RG16_FLOAT  :
            case api::Texture::Format::RG32_FLOAT  : return glf::Texture::BaseFormat::RG;
            
            case api::Texture::Format::RGB8_UNORM  :
            case api::Texture::Format::RGB16_UNORM :
            case api::Texture::Format::RGB8_SNORM  :
            case api::Texture::Format::RGB16_SNORM :
            case api::Texture::Format::RGB8_SRGB   :
            case api::Texture::Format::RGB16_FLOAT :
            case api::Texture::Format::RGB32_FLOAT : return glf::Texture::BaseFormat::RGB;
            
            case api::Texture::Format::RGBA8_UNORM :
            case api::Texture::Format::RGBA16_UNORM:
            case api::Texture::Format::RGBA8_SNORM :
            case api::Texture::Format::RGBA16_SNORM:
            case api::Texture::Format::RGBA8_SRGB  :
            case api::Texture::Format::RGBA16_FLOAT:
            case api::Texture::Format::RGBA32_FLOAT: return glf::Texture::BaseFormat::RGBA;
            
            case api::Texture::Format::D16_UNORM   :
            case api::Texture::Format::D24_UNORM   :
            case api::Texture::Format::D32_FLOAT   : return glf::Texture::BaseFormat::D;
            
            case api::Texture::Format::S8_UINT     : return glf::Texture::BaseFormat::S;

            default: throw std::invalid_argument{ "Invalid texture format!" };
        }
    }
    static auto map_texture_format                       (api::Texture::Format format)
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM         : return glf::Texture::Format::R8_UNORM;
            case api::Texture::Format::RG8_UNORM        : return glf::Texture::Format::RG8_UNORM;
            case api::Texture::Format::RGB8_UNORM       : return glf::Texture::Format::RGB8_UNORM;
            case api::Texture::Format::RGBA8_UNORM      : return glf::Texture::Format::RGBA8_UNORM;
            case api::Texture::Format::R16_UNORM        : return glf::Texture::Format::R16_UNORM;
            case api::Texture::Format::RG16_UNORM       : return glf::Texture::Format::RG16_UNORM;
            case api::Texture::Format::RGB16_UNORM      : return glf::Texture::Format::RGB16_UNORM;
            case api::Texture::Format::RGBA16_UNORM     : return glf::Texture::Format::RGBA16_UNORM;
            case api::Texture::Format::R8_SNORM         : return glf::Texture::Format::R8_SNORM;
            case api::Texture::Format::RG8_SNORM        : return glf::Texture::Format::RG8_SNORM;
            case api::Texture::Format::RGB8_SNORM       : return glf::Texture::Format::RGB8_SNORM;
            case api::Texture::Format::RGBA8_SNORM      : return glf::Texture::Format::RGBA8_SNORM;
            case api::Texture::Format::R16_SNORM        : return glf::Texture::Format::R16_SNORM;
            case api::Texture::Format::RG16_SNORM       : return glf::Texture::Format::RG16_SNORM;
            case api::Texture::Format::RGB16_SNORM      : return glf::Texture::Format::RGB16_SNORM;
            case api::Texture::Format::RGBA16_SNORM     : return glf::Texture::Format::RGBA16_SNORM;
            case api::Texture::Format::RGB8_SRGB        : return glf::Texture::Format::RGB8_SRGB;
            case api::Texture::Format::RGBA8_SRGB       : return glf::Texture::Format::RGBA8_SRGB;
            case api::Texture::Format::R16_FLOAT        : return glf::Texture::Format::R16_FLOAT;
            case api::Texture::Format::RG16_FLOAT       : return glf::Texture::Format::RG16_FLOAT;
            case api::Texture::Format::RGB16_FLOAT      : return glf::Texture::Format::RGB16_FLOAT;
            case api::Texture::Format::RGBA16_FLOAT     : return glf::Texture::Format::RGBA16_FLOAT;
            case api::Texture::Format::R32_FLOAT        : return glf::Texture::Format::R32_FLOAT;
            case api::Texture::Format::RG32_FLOAT       : return glf::Texture::Format::RG32_FLOAT;
            case api::Texture::Format::RGB32_FLOAT      : return glf::Texture::Format::RGB32_FLOAT;
            case api::Texture::Format::RGBA32_FLOAT     : return glf::Texture::Format::RGBA32_FLOAT;
            case api::Texture::Format::D16_UNORM        : return glf::Texture::Format::D16_UNORM;
            case api::Texture::Format::D24_UNORM        : return glf::Texture::Format::D24_UNORM;
            case api::Texture::Format::D32_FLOAT        : return glf::Texture::Format::D32_FLOAT;
            case api::Texture::Format::D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case api::Texture::Format::D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            case api::Texture::Format::S8_UINT          : return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static auto map_texture_format_type                  (api::Texture::Format format)
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM: 
            case api::Texture::Format::RG8_UNORM: 
            case api::Texture::Format::RGB8_UNORM: 
            case api::Texture::Format::RGBA8_UNORM:       return glf::PixelData::Type::UnsignedByte;

            case api::Texture::Format::R16_UNORM: 
            case api::Texture::Format::RG16_UNORM: 
            case api::Texture::Format::RGB16_UNORM: 
            case api::Texture::Format::RGBA16_UNORM:      return glf::PixelData::Type::UnsignedShort;

            case api::Texture::Format::R8_SNORM: 
            case api::Texture::Format::RG8_SNORM: 
            case api::Texture::Format::RGB8_SNORM: 
            case api::Texture::Format::RGBA8_SNORM:       return glf::PixelData::Type::Byte;

            case api::Texture::Format::R16_SNORM: 
            case api::Texture::Format::RG16_SNORM: 
            case api::Texture::Format::RGB16_SNORM: 
            case api::Texture::Format::RGBA16_SNORM:      return glf::PixelData::Type::Short;

            case api::Texture::Format::RGB8_SRGB: 
            case api::Texture::Format::RGBA8_SRGB:        return glf::PixelData::Type::UnsignedByte;
            
            case api::Texture::Format::R16_FLOAT: 
            case api::Texture::Format::RG16_FLOAT: 
            case api::Texture::Format::RGB16_FLOAT: 
            case api::Texture::Format::RGBA16_FLOAT:      return glf::PixelData::Type::HalfFloat;
            
            case api::Texture::Format::R32_FLOAT: 
            case api::Texture::Format::RG32_FLOAT: 
            case api::Texture::Format::RGB32_FLOAT: 
            case api::Texture::Format::RGBA32_FLOAT:      return glf::PixelData::Type::Float;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static auto map_texture_min_filter                   (api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return glf::Texture::MinificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return glf::Texture::MinificationFilter::NearestMipmapNearest;
            case api::Texture::Filter::Bilinear:  return glf::Texture::MinificationFilter::LinearMipmapNearest;
            case api::Texture::Filter::Trilinear: return glf::Texture::MinificationFilter::LinearMipmapLinear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static auto map_texture_mag_filter                   (api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return glf::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return glf::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Bilinear:  return glf::Texture::MagnificationFilter::Linear;
            case api::Texture::Filter::Trilinear: return glf::Texture::MagnificationFilter::Linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static auto map_texture_wrapping                     (api::Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case api::Texture::Wrapping::ClampToEdge:         return glf::Texture::Wrapping::ClampToEdge;
            case api::Texture::Wrapping::ClampToBorder:       return glf::Texture::Wrapping::ClampToBorder;
            case api::Texture::Wrapping::Repeat:              return glf::Texture::Wrapping::Repeat;
            case api::Texture::Wrapping::MirroredRepeat:      return glf::Texture::Wrapping::MirroredRepeat;
            case api::Texture::Wrapping::MirroredClampToEdge: return glf::Texture::Wrapping::MirroredClampToEdge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    
    static auto map_render_buffer_format                 (api::RenderBuffer::Format format)
    {
        switch (format)
        {
            case api::RenderBuffer::Format::R8_UNORM:          return glf::RenderBuffer::Format::R8;
            case api::RenderBuffer::Format::RG8_UNORM:         return glf::RenderBuffer::Format::RG8;
            case api::RenderBuffer::Format::RGB8_UNORM:        return glf::RenderBuffer::Format::RGB8;
            case api::RenderBuffer::Format::RGBA8_UNORM:       return glf::RenderBuffer::Format::RGBA8;
            case api::RenderBuffer::Format::RGBA8_SRGB:        return glf::RenderBuffer::Format::RGBA8_SRGB;
            case api::RenderBuffer::Format::D16_UNORM:         return glf::RenderBuffer::Format::D16_UNORM;
            case api::RenderBuffer::Format::D24_UNORM:         return glf::RenderBuffer::Format::D24_UNORM;
            case api::RenderBuffer::Format::D32_FLOAT:         return glf::RenderBuffer::Format::D32_FLOAT;
            case api::RenderBuffer::Format::D24_UNORM_S8_UINT: return glf::RenderBuffer::Format::D24_UNORM_S8_UINT;
            case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return glf::RenderBuffer::Format::D32_FLOAT_S8_UINT;
            case api::RenderBuffer::Format::S8_UINT:           return glf::RenderBuffer::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    
    static auto map_cubemap_texture_format_base          (api::Cubemap::Format format)
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM    :
            case api::Cubemap::Format::R16_UNORM   :
            case api::Cubemap::Format::R8_SNORM    :
            case api::Cubemap::Format::R16_SNORM   :
            case api::Cubemap::Format::R16_FLOAT   :
            case api::Cubemap::Format::R32_FLOAT   : return glf::Texture::BaseFormat::R;
            
            case api::Cubemap::Format::RG8_UNORM   :
            case api::Cubemap::Format::RG16_UNORM  :
            case api::Cubemap::Format::RG8_SNORM   :
            case api::Cubemap::Format::RG16_SNORM  :
            case api::Cubemap::Format::RG16_FLOAT  :
            case api::Cubemap::Format::RG32_FLOAT  : return glf::Texture::BaseFormat::RG;
            
            case api::Cubemap::Format::RGB8_UNORM  :
            case api::Cubemap::Format::RGB16_UNORM :
            case api::Cubemap::Format::RGB8_SNORM  :
            case api::Cubemap::Format::RGB16_SNORM :
            case api::Cubemap::Format::RGB8_SRGB   :
            case api::Cubemap::Format::RGB16_FLOAT :
            case api::Cubemap::Format::RGB32_FLOAT : return glf::Texture::BaseFormat::RGB;
            
            case api::Cubemap::Format::RGBA8_UNORM :
            case api::Cubemap::Format::RGBA16_UNORM:
            case api::Cubemap::Format::RGBA8_SNORM :
            case api::Cubemap::Format::RGBA16_SNORM:
            case api::Cubemap::Format::RGBA8_SRGB  :
            case api::Cubemap::Format::RGBA16_FLOAT:
            case api::Cubemap::Format::RGBA32_FLOAT: return glf::Texture::BaseFormat::RGBA;
            
            case api::Cubemap::Format::D16_UNORM   :
            case api::Cubemap::Format::D24_UNORM   :
            case api::Cubemap::Format::D32_FLOAT   : return glf::Texture::BaseFormat::D;
            
            case api::Cubemap::Format::S8_UINT     : return glf::Texture::BaseFormat::S;

            default: throw std::invalid_argument{ "Invalid cubemap format!" };
        }
    }
    static auto map_cubemap_texture_format               (api::Cubemap::Format format)
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM:          return glf::Texture::Format::R8_UNORM;
            case api::Cubemap::Format::RG8_UNORM:         return glf::Texture::Format::RG8_UNORM;
            case api::Cubemap::Format::RGB8_UNORM:        return glf::Texture::Format::RGB8_UNORM;
            case api::Cubemap::Format::RGBA8_UNORM:       return glf::Texture::Format::RGBA8_UNORM;
            case api::Cubemap::Format::R16_UNORM:         return glf::Texture::Format::R16_UNORM;
            case api::Cubemap::Format::RG16_UNORM:        return glf::Texture::Format::RG16_UNORM;
            case api::Cubemap::Format::RGB16_UNORM:       return glf::Texture::Format::RGB16_UNORM;
            case api::Cubemap::Format::RGBA16_UNORM:      return glf::Texture::Format::RGBA16_UNORM;
            case api::Cubemap::Format::R8_SNORM:          return glf::Texture::Format::R8_SNORM;
            case api::Cubemap::Format::RG8_SNORM:         return glf::Texture::Format::RG8_SNORM;
            case api::Cubemap::Format::RGB8_SNORM:        return glf::Texture::Format::RGB8_SNORM;
            case api::Cubemap::Format::RGBA8_SNORM:       return glf::Texture::Format::RGBA8_SNORM;
            case api::Cubemap::Format::R16_SNORM:         return glf::Texture::Format::R16_SNORM;
            case api::Cubemap::Format::RG16_SNORM:        return glf::Texture::Format::RG16_SNORM;
            case api::Cubemap::Format::RGB16_SNORM:       return glf::Texture::Format::RGB16_SNORM;
            case api::Cubemap::Format::RGBA16_SNORM:      return glf::Texture::Format::RGBA16_SNORM;
            case api::Cubemap::Format::RGB8_SRGB:         return glf::Texture::Format::RGB8_SRGB;
            case api::Cubemap::Format::RGBA8_SRGB:        return glf::Texture::Format::RGBA8_SRGB;
            case api::Cubemap::Format::R16_FLOAT:         return glf::Texture::Format::R16_FLOAT;
            case api::Cubemap::Format::RG16_FLOAT:        return glf::Texture::Format::RG16_FLOAT;
            case api::Cubemap::Format::RGB16_FLOAT:       return glf::Texture::Format::RGB16_FLOAT;
            case api::Cubemap::Format::RGBA16_FLOAT:      return glf::Texture::Format::RGBA16_FLOAT;
            case api::Cubemap::Format::R32_FLOAT:         return glf::Texture::Format::R32_FLOAT;
            case api::Cubemap::Format::RG32_FLOAT:        return glf::Texture::Format::RG32_FLOAT;
            case api::Cubemap::Format::RGB32_FLOAT:       return glf::Texture::Format::RGB32_FLOAT;
            case api::Cubemap::Format::RGBA32_FLOAT:      return glf::Texture::Format::RGBA32_FLOAT;
            case api::Cubemap::Format::D16_UNORM:         return glf::Texture::Format::D16_UNORM;
            case api::Cubemap::Format::D24_UNORM:         return glf::Texture::Format::D24_UNORM;
            case api::Cubemap::Format::D32_FLOAT:         return glf::Texture::Format::D32_FLOAT;
            case api::Cubemap::Format::D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case api::Cubemap::Format::D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            case api::Cubemap::Format::S8_UINT:           return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static auto map_cubemap_texture_format_type          (api::Cubemap::Format format)
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM: 
            case api::Cubemap::Format::RG8_UNORM: 
            case api::Cubemap::Format::RGB8_UNORM: 
            case api::Cubemap::Format::RGBA8_UNORM:       return glf::PixelData::Type::UnsignedByte;

            case api::Cubemap::Format::R16_UNORM:
            case api::Cubemap::Format::RG16_UNORM:
            case api::Cubemap::Format::RGB16_UNORM:
            case api::Cubemap::Format::RGBA16_UNORM:      return glf::PixelData::Type::UnsignedShort;

            case api::Cubemap::Format::R8_SNORM:
            case api::Cubemap::Format::RG8_SNORM:
            case api::Cubemap::Format::RGB8_SNORM:
            case api::Cubemap::Format::RGBA8_SNORM:       return glf::PixelData::Type::Byte;

            case api::Cubemap::Format::R16_SNORM:
            case api::Cubemap::Format::RG16_SNORM:
            case api::Cubemap::Format::RGB16_SNORM:
            case api::Cubemap::Format::RGBA16_SNORM:      return glf::PixelData::Type::Short;

            case api::Cubemap::Format::RGB8_SRGB: 
            case api::Cubemap::Format::RGBA8_SRGB:        return glf::PixelData::Type::UnsignedByte;
            
            case api::Cubemap::Format::R16_FLOAT: 
            case api::Cubemap::Format::RG16_FLOAT: 
            case api::Cubemap::Format::RGB16_FLOAT: 
            case api::Cubemap::Format::RGBA16_FLOAT:      return glf::PixelData::Type::HalfFloat;
            
            case api::Cubemap::Format::R32_FLOAT:
            case api::Cubemap::Format::RG32_FLOAT:
            case api::Cubemap::Format::RGB32_FLOAT:
            case api::Cubemap::Format::RGBA32_FLOAT:      return glf::PixelData::Type::Float;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    
    static auto map_frame_buffer_target                  (api::FrameBuffer::Target  target)
    {
        switch (target)
        {
            case api::FrameBuffer::Target::Read:  return glf::FrameBuffer::Target::Read;
            case api::FrameBuffer::Target::Write: return glf::FrameBuffer::Target::Write;

            default: throw std::invalid_argument{ "Invalid framebuffer target!" };
        }
    }
    static auto map_frame_buffer_attachment              (api::FrameBuffer::Attachment attachment)
    {
        switch (attachment)
        {
            case api::FrameBuffer::Attachment::Color0:       return glf::FrameBuffer::Attachment::ColorIndex + 0u; 
            case api::FrameBuffer::Attachment::Color1:       return glf::FrameBuffer::Attachment::ColorIndex + 1u; 
            case api::FrameBuffer::Attachment::Color2:       return glf::FrameBuffer::Attachment::ColorIndex + 2u; 
            case api::FrameBuffer::Attachment::Color3:       return glf::FrameBuffer::Attachment::ColorIndex + 3u; 
            case api::FrameBuffer::Attachment::Color4:       return glf::FrameBuffer::Attachment::ColorIndex + 4u; 
            case api::FrameBuffer::Attachment::Color5:       return glf::FrameBuffer::Attachment::ColorIndex + 5u; 
            case api::FrameBuffer::Attachment::Color6:       return glf::FrameBuffer::Attachment::ColorIndex + 6u; 
            case api::FrameBuffer::Attachment::Color7:       return glf::FrameBuffer::Attachment::ColorIndex + 7u; 
            
            case api::FrameBuffer::Attachment::Depth:        return glf::FrameBuffer::Attachment::Depth;
            case api::FrameBuffer::Attachment::Stencil:      return glf::FrameBuffer::Attachment::Stencil;
            case api::FrameBuffer::Attachment::DepthStencil: return glf::FrameBuffer::Attachment::DepthStencil;
        }
    }
    static auto map_frame_buffer_texture_attachment      (api::Texture::Format      format)
	{
		switch (format)
		{
			case api::Texture::Format::D16_UNORM:
			case api::Texture::Format::D24_UNORM:
			case api::Texture::Format::D32_FLOAT:         return glf::FrameBuffer::Attachment::Depth;

			case api::Texture::Format::D24_UNORM_S8_UINT:
			case api::Texture::Format::D32_FLOAT_S8_UINT: return glf::FrameBuffer::Attachment::DepthStencil;

			case api::Texture::Format::S8_UINT:           return glf::FrameBuffer::Attachment::Stencil;

			default:                                      return glf::FrameBuffer::Attachment::ColorIndex;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
	static auto map_frame_buffer_cubemap_attachment      (api::Cubemap::Format      format)
	{
		switch (format)
		{
			case api::Cubemap::Format::D16_UNORM:
			case api::Cubemap::Format::D24_UNORM:
			case api::Cubemap::Format::D32_FLOAT:         return glf::FrameBuffer::Attachment::Depth;

			case api::Cubemap::Format::D24_UNORM_S8_UINT:
			case api::Cubemap::Format::D32_FLOAT_S8_UINT: return glf::FrameBuffer::Attachment::DepthStencil;

			case api::Cubemap::Format::S8_UINT:           return glf::FrameBuffer::Attachment::Stencil;

			default:                                      return glf::FrameBuffer::Attachment::ColorIndex;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}
	static auto map_frame_buffer_render_buffer_attachment(api::RenderBuffer::Format format)
	{
		switch (format)
		{
			case api::RenderBuffer::Format::D16_UNORM:
			case api::RenderBuffer::Format::D24_UNORM:
			case api::RenderBuffer::Format::D32_FLOAT:         return glf::FrameBuffer::Attachment::Depth;

			case api::RenderBuffer::Format::D24_UNORM_S8_UINT:
			case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return glf::FrameBuffer::Attachment::DepthStencil;

			case api::RenderBuffer::Format::S8_UINT:           return glf::FrameBuffer::Attachment::Stencil;

			default:                                           return glf::FrameBuffer::Attachment::ColorIndex;
		}

		throw std::invalid_argument{ "Invalid format!" };
	}

    static auto map_program_stage                        (api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return glf::Program::Stage::Vertex;
            case api::Shader::Stage::TessellationControl:    return glf::Program::Stage::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return glf::Program::Stage::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return glf::Program::Stage::Geometry;
            case api::Shader::Stage::Fragment:               return glf::Program::Stage::Fragment;
            case api::Shader::Stage::Compute:                return glf::Program::Stage::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    
    static auto map_shader_type                          (api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return glf::Shader::Type::Vertex;
            case api::Shader::Stage::TessellationControl:    return glf::Shader::Type::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return glf::Shader::Type::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return glf::Shader::Type::Geometry;
            case api::Shader::Stage::Fragment:               return glf::Shader::Type::Fragment;
            case api::Shader::Stage::Compute:                return glf::Shader::Type::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    
    static auto map_depth_function                       (api::RenderState::DepthFunction depthFunction)
    {
        switch (depthFunction)
        {
            case api::RenderState::DepthFunction::Always:       return glf::DepthFunction::Always;
            case api::RenderState::DepthFunction::Never:        return glf::DepthFunction::Never;
            case api::RenderState::DepthFunction::Equal:        return glf::DepthFunction::Equal;
            case api::RenderState::DepthFunction::NotEqual:     return glf::DepthFunction::NotEqual;
            case api::RenderState::DepthFunction::Less:         return glf::DepthFunction::Less;
            case api::RenderState::DepthFunction::LessEqual:    return glf::DepthFunction::LessEqual;
            case api::RenderState::DepthFunction::Greater:      return glf::DepthFunction::Greater;
            case api::RenderState::DepthFunction::GreaterEqual: return glf::DepthFunction::GreaterEqual;

            default: throw std::invalid_argument{ "Invalid depth function!" };
        }
    }
    
    static auto map_culling_face                         (api::RenderState::FaceCulling cullingFace)
    {
        switch (cullingFace)
        {
            case api::RenderState::FaceCulling::Front:     return glf::Culling::Facet::Front;
            case api::RenderState::FaceCulling::Back:      return glf::Culling::Facet::Back;
            case api::RenderState::FaceCulling::FrontBack: return glf::Culling::Facet::FrontBack;

            default: throw std::invalid_argument{ "Invalid culling face!" };
        }
    }
}
