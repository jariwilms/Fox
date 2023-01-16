#pragma once

#include "stdafx.hpp"

//OpenGL
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"

namespace hlx
{
    class GraphicsAPI
    {
    public:
        template<typename T, typename... Args>
        static std::shared_ptr<T> create(Args... args) = delete;



        template<> static std::shared_ptr<VertexArray>  create()
        {
            return std::make_shared<OpenGLVertexArray>();
        }
        //template<> static std::shared_ptr<VertexArray>  create(std::initializer_list<std::pair<const std::shared_ptr<VertexBuffer>, const std::shared_ptr<VertexLayout>>> vertices, const std::shared_ptr<IndexBuffer> indices)
        //{
        //    return std::make_shared<OpenGLVertexArray>(vertices, indices);
        //}
        
        //template<> static std::shared_ptr<VertexBuffer> create(size_t size)
        //{
        //    return std::make_shared<OpenGLVertexBuffer>(size);
        //}
        
        //template<> static std::shared_ptr<IndexBuffer>  create(size_t size)
        //{
        //    return std::make_shared<OpenGLIndexBuffer>(size);
        //}
        //template<> static std::shared_ptr<IndexBuffer>  create(const std::vector<unsigned int>& data)
        //{
        //    return std::make_shared<OpenGLIndexBuffer>(data);
        //}
        template<typename T, typename U>
        static std::shared_ptr<VertexBuffer> create_t(const std::vector<U>& data)
        {
            return std::make_shared<OpenGLVertexBuffer>(data.size() * sizeof(T), data.data());
        }
        template<typename T, typename U>
        static std::shared_ptr<T> create_s(const std::vector<U>& data) = delete;
        template<> static std::shared_ptr<IndexBuffer> create_s(const std::vector<unsigned int>& data)
        {
            return std::make_shared<OpenGLIndexBuffer>(data.size() * sizeof(unsigned int), data.data());
        }


        
        template<> static std::shared_ptr<FrameBuffer>  create(const glm::uvec2& dimensions)
        {
            return std::make_shared<OpenGLFrameBuffer>(dimensions);
        }
        template<> static std::shared_ptr<RenderBuffer> create(RenderBuffer::Type type, RenderBuffer::Layout layout, unsigned int samples, const glm::uvec2& dimensions)
        {
            return std::make_shared<OpenGLRenderBuffer>(type, layout, samples, dimensions);
        }
    };
}
