#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/Buffer/Buffer.hpp"
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Buffer/VertexArray.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL

        template<api::Buffer::Type TYPE>
        using BufferObject = api::gl::BufferObject<TYPE>;
        using VertexArray  = api::gl::VertexArray;
#endif
    }



    class VertexArray
    {
    public:
        static inline auto create()
        {
            return std::shared_ptr<VertexArray>(new VertexArray{});
        }

        void bind()
        {
            _->bind();
        }

        void enable_attribute(fox::uint32_t index)
        {
            _->enable_attribute(index);
        }
        void disable_attribute(fox::uint32_t index)
        {
            _->disable_attribute(index);
        }

        void set_attribute_divisor(fox::uint32_t attribute, fox::uint32_t divisor)
        {
            _->set_attribute_divisor(attribute, divisor);
        }

        template<typename T>
        void tie(std::shared_ptr<const gfx::VertexBuffer<T>> buffer, gfx::VertexLayout layout)
        {
            _->tie(buffer->handle(), layout);
        }
        void tie(std::shared_ptr<const gfx::IndexBuffer> buffer)
        {
            _->tie(buffer->impl());
        }

        const std::unordered_map<fox::uint32_t, gfx::handle_t>& binding_points() const
        {
            return _->binding_points();
        }
        const std::unordered_map<fox::uint32_t, gfx::handle_t>& attributes()     const
        {
            return _->attributes();
        }

        fox::count_t  index_count() const
        {
            return _->index_count();
        }
        gfx::handle_t handle()      const
        {
            return _->handle();
        }

    protected:
        VertexArray()
            : _{ std::make_shared<impl::VertexArray>() } {}

        std::shared_ptr<impl::VertexArray> _;
    };
}
