#pragma once

#include "Fox/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Fox/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Fox/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Fox/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"
#include "Fox/Rendering/API/OpenGL/RenderState/OpenGLRenderState.hpp"
#include "Fox/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"
#include "Fox/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace fox::gfx
{
    using Dimensions   = api::Dimensions;
    using AntiAliasing = api::AntiAliasing;

    using Buffer                 = api::Buffer;
    template<Buffer::Access ACCESS, typename T>
    using VertexBuffer           = api::gl::OpenGLBuffer<Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = api::gl::OpenGLBuffer<Buffer::Type::Index, ACCESS, std::uint32_t>;
    template<typename T>
    using UniformBuffer          = api::gl::OpenGLBuffer<Buffer::Type::Uniform, Buffer::Access::Dynamic, T>;
    template<Buffer::Access ACCESS, typename T>
    using UniformArrayBuffer     = api::gl::OpenGLBuffer<Buffer::Type::UniformArray, ACCESS, T>;

    using VertexArray            = api::gl::OpenGLVertexArray;

    template<typename... T>
    using VertexLayout           = api::gl::OpenGLVertexLayout<T...>;

    using FrameBuffer            = api::gl::OpenGLFrameBuffer<AntiAliasing::None>;
    using FrameBufferMultisample = api::gl::OpenGLFrameBuffer<AntiAliasing::MSAA>;

    using Pipeline               = api::gl::OpenGLPipeline;
    using Shader                 = api::gl::OpenGLShader;

    using Texture                = api::Texture;
    using Texture1D              = api::gl::OpenGLTexture<Dimensions::_1D, AntiAliasing::None>;
    using Texture2D              = api::gl::OpenGLTexture<Dimensions::_2D, AntiAliasing::None>;
    using Texture3D              = api::gl::OpenGLTexture<Dimensions::_3D, AntiAliasing::None>;
    using Texture2DMultisample   = api::gl::OpenGLTexture<Dimensions::_2D, AntiAliasing::MSAA>;
    using Texture3DMultisample   = api::gl::OpenGLTexture<Dimensions::_3D, AntiAliasing::MSAA>;

    using TextureBlueprint       = api::TextureBlueprint;

    using RenderState            = api::gl::OpenGLRenderState;
}
