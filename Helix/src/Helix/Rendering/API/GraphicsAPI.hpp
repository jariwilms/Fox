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
                                                       
        static std::shared_ptr<VertexBuffer>        create_vbo(unsigned int count)
        {
            return std::make_shared<OpenGLVertexBuffer>(count);
        }
        template<typename T>                           
        static std::shared_ptr<VertexBuffer>        create_vbo(std::span<const T> data)
        {
            return std::make_shared<OpenGLVertexBuffer>(data);
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
                                                       
        static std::shared_ptr<FrameBuffer>            create_fbo(const Vector2u& dimensions, std::span<const std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> textures, std::span<const std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> renderBuffers)
        {
            return std::make_shared<OpenGLFrameBuffer>(dimensions, textures, renderBuffers);
        }
        static std::shared_ptr<FrameBufferMultisample> create_fbo_ms(const Vector2u& dimensions, unsigned int samples, std::span<const std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> textures, std::span<const std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> renderBuffers)
        {
            return std::make_shared<OpenGLFrameBufferMultisample>(dimensions, samples, textures, renderBuffers);
        }
        static std::shared_ptr<RenderBuffer>           create_rbo(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions)
        {
            return std::make_shared<OpenGLRenderBuffer>(type, layout, dimensions);
        }
        static std::shared_ptr<RenderBuffer>           create_rbo_ms(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int samples)
        {
            return std::make_shared<OpenGLRenderBufferMultisample>(type, layout, dimensions, samples);
        }
                                                       
        static std::shared_ptr<Shader>                 create_sho(Shader::Stage stage, std::span<const byte> binary)
        {
            return std::make_shared<OpenGLShader>(stage, binary);
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
            auto vertexShader = GraphicsAPI::create_sho(Shader::Stage::Vertex, *vertexSource);
            auto fragmentShader = GraphicsAPI::create_sho(Shader::Stage::Fragment, *fragmentSource);

            return create_plo({ vertexShader, fragmentShader });
        }

        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector2u& dimensions)
        {
            return std::make_shared<OpenGLTexture2D>(format, filter, wrapping, dimensions);
        }
        template<typename T>
        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector2u& dimensions, Texture::Components dataComponents, std::span<const T> data)
        {
            return std::make_shared<OpenGLTexture2D>(format, filter, wrapping, dimensions, dataComponents, typeid(T), utl::as_bytes(data));
        }
        static std::shared_ptr<Texture2DMultisample>   create_tex_ms(Texture::Format format, const Vector2u& dimensions, unsigned int samples)
        {
            return std::make_shared<OpenGLTexture2DMultisample>(format, dimensions, samples);
        }
    };
    //class Test
    //{
    //    template<typename T, typename... Args> std::shared_ptr<T> create(Args... args) = delete;
    //    template<> std::shared_ptr<Shader> create<Shader>(int a, int b)
    //    {

    //    }
    //    template<> std::shared_ptr<Pipeline> create<Pipeline>(int a, int b)
    //    {

    //    }
    //};
}
