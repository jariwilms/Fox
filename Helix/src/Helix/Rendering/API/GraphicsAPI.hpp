#pragma once

#include "stdafx.hpp"

#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBufferMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBufferMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformArrayBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2DMultisample.hpp"
#include "Helix/Rendering/Buffer/UniformArrayBuffer.hpp"

namespace hlx
{
    class GraphicsAPI
    {
    public:
        //TODO: complete refactor of all these methods => single create<typename T> func?

        static std::shared_ptr<VertexArray>            create_vao()
        {
            return std::make_shared<OpenGLVertexArray>();
        }
                                                       
        template<typename T>                           
        static std::shared_ptr<VertexBuffer<T>>        create_vbo(unsigned int count)
        {
            return std::make_shared<OpenGLVertexBuffer<T>>(count);
        }
        template<typename T>                           
        static std::shared_ptr<VertexBuffer<T>>        create_vbo(std::span<const T> data)
        {
            return std::make_shared<OpenGLVertexBuffer<T>>(data);
        }
        static std::shared_ptr<IndexBuffer>            create_ibo(unsigned int count)
        {
            return std::make_shared<OpenGLIndexBuffer>(count);
        }
        static std::shared_ptr<IndexBuffer>            create_ibo(std::span<const unsigned int> data)
        {
            return std::make_shared<OpenGLIndexBuffer>(data);
        }
        template<typename T>                           
        static std::shared_ptr<UniformBuffer<T>>       create_ubo(unsigned int binding)
        {
            return std::make_shared<OpenGLUniformBuffer<T>>(binding);
        }
        template<typename T>                           
        static std::shared_ptr<UniformBuffer<T>>       create_ubo(unsigned int binding, const T& data)
        {
            return std::make_shared<OpenGLUniformBuffer<T>>(binding, data);
        }
        template<typename T>                           
        static std::shared_ptr<UniformArrayBuffer<T>>  create_uba(unsigned int count, unsigned int binding)
        {
            return std::make_shared<OpenGLUniformArrayBuffer<T>>(count, binding);
        }
        template<typename T>                           
        static std::shared_ptr<UniformArrayBuffer<T>>  create_uba(unsigned int binding, std::span<const T> data)
        {
            return std::make_shared<OpenGLUniformArrayBuffer<T>>(binding, data);
        }
                                                       
        static std::shared_ptr<FrameBuffer>            create_fbo(const Vector2u& dimensions, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>>& renderBuffers)
        {
            return std::make_shared<OpenGLFrameBuffer>(dimensions, textures, renderBuffers);
        }
        static std::shared_ptr<FrameBufferMultisample> create_fbo_ms(const Vector2u& dimensions, unsigned int samples, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>>& renderBuffers)
        {
            return std::make_shared<OpenGLFrameBufferMultisample>(dimensions, samples, textures, renderBuffers);
        }
        static std::shared_ptr<RenderBuffer>           create_rbo(RenderBuffer::Type type, RenderBuffer::Layout colorDepth, const Vector2u& dimensions)
        {
            return std::make_shared<OpenGLRenderBuffer>(type, colorDepth, dimensions);
        }
        static std::shared_ptr<RenderBuffer>           create_rbo_ms(RenderBuffer::Type type, RenderBuffer::Layout colorDepth, const Vector2u& dimensions, unsigned int multiSamples)
        {
            return std::make_shared<OpenGLRenderBufferMultisample>(type, colorDepth, dimensions, multiSamples);
        }
                                                       
        static std::shared_ptr<Shader>                 create_sho(Shader::Type type, std::span<const byte> binary)
        {
            return std::make_shared<OpenGLShader>(type, binary);
        }
        static std::shared_ptr<Pipeline>               create_plo()
        {
            return std::make_shared<OpenGLPipeline>();
        }
        static std::shared_ptr<Pipeline>               create_plo(std::initializer_list<const std::shared_ptr<Shader>> shaders)
        {
            return std::make_shared<OpenGLPipeline>(shaders);
        }
        static std::shared_ptr<Pipeline>               create_plo(const std::string& vertexPath, const std::string& fragmentPath) //TODO: optional geometry/tessellation stages
        {
            const auto vertexSource = IO::load<File>(vertexPath)->read();
            const auto fragmentSource = IO::load<File>(fragmentPath)->read();
            auto vertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *vertexSource);
            if (!vertexShader->valid()) throw std::runtime_error{ vertexShader->error().data() };
            auto fragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *fragmentSource);
            if (!fragmentShader->valid()) throw std::runtime_error{ fragmentShader->error().data() };

            return create_plo({ vertexShader, fragmentShader });
        }

        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::ColorDepth colorDepth, const Vector2u& dimensions, Texture::Filter filter, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, unsigned int mipLevels, bool sRGB)
        {
            return std::make_shared<OpenGLTexture2D>(format, colorDepth, dimensions, filter, wrappingS, wrappingT, mipLevels, sRGB);
        }
        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::ColorDepth colorDepth, const Vector2u& dimensions, Texture::Filter filter, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, unsigned int mipLevels, bool sRGB, Texture::Format dataFormat, std::span<const byte> data)
        {
            return std::make_shared<OpenGLTexture2D>(format, colorDepth, dimensions, filter, wrappingS, wrappingT, mipLevels, sRGB, dataFormat, data);
        }
        
        static std::shared_ptr<Texture2DMultisample>   create_tex_ms(Texture::Format format, Texture::ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB)
        {
            return std::make_shared<OpenGLTexture2DMultisample>(format, colorDepth, dimensions, mipLevels, samples, sRGB);
        }
        static std::shared_ptr<Texture2DMultisample>   create_tex_ms(Texture::Format format, Texture::ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB, Texture::Format dataFormat, std::span<const byte> data)
        {
            return std::make_shared<OpenGLTexture2DMultisample>(format, colorDepth, dimensions, mipLevels, samples, sRGB, dataFormat, data);
        }
    };
}
