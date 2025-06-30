#pragma once

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/layout/vertex_layout.hpp>

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

        void set_attribute_divisor(gfx::binding_t binding, fox::uint32_t divisor)
        {
            _->set_attribute_divisor(binding, divisor);
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

        auto index_count() const -> fox::count_t
        {
            return _->index_count();
        }
        auto handle     () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl       () const -> std::shared_ptr<impl::VertexArray>
        {
            return _;
        }

    protected:
        VertexArray()
            : _{ std::make_shared<impl::VertexArray>() } {}

        std::shared_ptr<impl::VertexArray> _;
    };
}
