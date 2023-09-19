#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformArrayBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2DMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLCubemapTexture.hpp"

namespace hlx::gfx
{
    //std::shared_ptr<VertexArray>            create_vertex_array();
    //std::shared_ptr<VertexBuffer>           create_vertex_buffer(std::size_t size);
    //template<typename T>                    
    //std::shared_ptr<VertexBuffer>           create_vertex_buffer(std::span<const T> data);
    //std::shared_ptr<IndexBuffer>            create_index_buffer(unsigned int count);
    //std::shared_ptr<IndexBuffer>            create_index_buffer(std::span<const unsigned int> data);

    //template<typename T>
    //std::shared_ptr<UniformBuffer<T>>       create_uniform_buffer(unsigned int binding);
    //template<typename T>
    //std::shared_ptr<UniformBuffer<T>>       create_uniform_buffer(unsigned int binding, const T& data);
    //template<typename T>
    //std::shared_ptr<UniformArrayBuffer<T>>  create_uniform_buffer_array(unsigned int binding, unsigned int count);
    //template<typename T>
    //std::shared_ptr<UniformArrayBuffer<T>>  create_uniform_buffer_array(unsigned int binding, std::span<const T> data);

    //std::shared_ptr<FrameBuffer>            create_framebuffer(const Vector2u& dimensions, std::span<const FrameBuffer::TextureManifest> textureManifest, std::span<const FrameBuffer::RenderBufferManifest> renderBufferManifest);
    //std::shared_ptr<FrameBufferMultisample> create_framebuffer_multisample(const Vector2u& dimensions, unsigned int samples, std::span<const FrameBuffer::TextureManifest> textureManifest, std::span<const FrameBuffer::RenderBufferManifest> renderBufferManifest);
    //std::shared_ptr<RenderBuffer>           create_renderbuffer(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions);
    //std::shared_ptr<RenderBuffer>           create_renderbuffer_multisample(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int samples);

    //std::shared_ptr<Shader>                 create_shader(Shader::Stage stage, std::span<const byte> binary);
    //std::shared_ptr<Pipeline>               create_pipeline();
    //std::shared_ptr<Pipeline>               create_pipeline(std::initializer_list<const std::shared_ptr<Shader>> shaders);
    //std::shared_ptr<Pipeline>               create_pipeline(const std::string& vertexPath, const std::string& fragmentPath);

    //std::shared_ptr<Texture2D>              create_texture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector2u& dimensions);
    //template<typename T>
    //std::shared_ptr<Texture2D>              create_texture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector2u& dimensions, Texture::Components components, std::span<const T> data);
    //std::shared_ptr<Texture2DMultisample>   create_texture_multisample(Texture::Format format, const Vector2u& dimensions, unsigned int samples);
}
