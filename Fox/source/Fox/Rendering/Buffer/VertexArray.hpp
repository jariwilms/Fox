#pragma once

#include "Fox/Rendering/Buffer/Buffer.hpp"
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"

namespace fox::gfx
{
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

        void enable_attribute (fox::index_t index)
        {
            _->enable_attribute(index);
        }
        void disable_attribute(fox::index_t index)
        {
            _->disable_attribute(index);
        }

        void set_attribute_divisor(fox::binding_t binding, fox::uint32_t divisor)
        {
            _->set_attribute_divisor(static_cast<impl::binding_t>(binding), divisor);
        }

        template<typename T>
        void tie(std::shared_ptr<const gfx::VertexBuffer<T>> buffer, const gfx::VertexLayout& layout)
        {
            _->tie(buffer->handle(), layout);
        }
        void tie(std::shared_ptr<const gfx::IndexBuffer>     buffer)
        {
            _->tie(buffer->handle(), buffer->count());
        }

        auto index_count() const
        {
            return _->index_count();
        }
        auto handle     () const
        {
            return _->handle();
        }
        auto impl       () const
        {
            return _;
        }

    protected:
        VertexArray()
            : _{ std::make_shared<impl::VertexArray>() } {}

        std::shared_ptr<impl::VertexArray> _;
    };
}
