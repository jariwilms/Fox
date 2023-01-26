#pragma once

#include "stdafx.hpp"

//OpenGL
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"

namespace hlx
{
    class GraphicsAPI
    {
    public:
        static std::shared_ptr<VertexArray>      create_vao()
        {
            return std::make_shared<OpenGLVertexArray>();
        }
        template<typename T>                     
        static std::shared_ptr<VertexBuffer<T>>  create_vbo(unsigned int count)
        {
            return std::make_shared<OpenGLVertexBuffer<T>>(count);
        }
        template<typename T>                     
        static std::shared_ptr<VertexBuffer<T>>  create_vbo(const std::span<T>& data)
        {
            return std::make_shared<OpenGLVertexBuffer<T>>(data);
        }
        static std::shared_ptr<IndexBuffer>      create_ibo(unsigned int count)
        {
            return std::make_shared<OpenGLIndexBuffer>(count);
        }
        static std::shared_ptr<IndexBuffer>      create_ibo(const std::span<unsigned int>& data)
        {
            return std::make_shared<OpenGLIndexBuffer>(data);
        }
        template<typename T>
        static std::shared_ptr<UniformBuffer<T>> create_ubo()
        {
            return std::make_shared<OpenGLUniformBuffer<T>>();
        }
        template<typename T>
        static std::shared_ptr<UniformBuffer<T>> create_ubo(const T& data)
        {
            return std::make_shared<OpenGLUniformBuffer<T>>(data);
        }

        static std::shared_ptr<FrameBuffer>      create_fbo(const glm::uvec2& dimensions, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>>& renderBuffers)
        {
            return std::make_shared<OpenGLFrameBuffer>(dimensions, textures, renderBuffers);
        }
        static std::shared_ptr<RenderBuffer>     create_rbo(RenderBuffer::Type type, RenderBuffer::Layout layout, const glm::uvec2& dimensions, unsigned int multiSamples)
        {
            return std::make_shared<OpenGLRenderBuffer>(type, layout, dimensions, multiSamples);
        }
                                                 
        static std::shared_ptr<Shader>           create_sho(Shader::Type type, const std::span<byte>& binary)
        {
            return std::make_shared<OpenGLShader>(type, binary);
        }
        static std::shared_ptr<Pipeline>         create_plo()
        {
            return std::make_shared<OpenGLPipeline>();
        }
        static std::shared_ptr<Pipeline>         create_plo(std::initializer_list<const std::shared_ptr<Shader>> shaders)
        {
            return std::make_shared<OpenGLPipeline>(shaders);
        }
                                                 
        static std::shared_ptr<Texture2D>        create_tex(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, unsigned int mipLevels)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels);
        }
        static std::shared_ptr<Texture2D>        create_tex(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, unsigned int mipLevels, const std::span<byte>& data)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels, data);
        }
        static std::shared_ptr<Texture2D>        create_tex(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter);
        }
        static std::shared_ptr<Texture2D>        create_tex(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, const std::span<byte>& data)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter, data);
        }
    };
}
