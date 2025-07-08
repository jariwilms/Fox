#pragma once

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/layout/layout.hpp>

namespace fox::gfx
{
    class VertexArray
    {
    public:
        VertexArray(std::shared_ptr<impl::VertexArray> _)
            : _{ _ } {}

        static auto create() -> std::shared_ptr<gfx::VertexArray>
        {
            return std::make_shared<fox::from_inaccessible_ctor<gfx::VertexArray>>();
        }

        void bind() const
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

        template<typename T, typename... attributes>
        void tie(std::shared_ptr<gfx::VertexBuffer<T>> buffer, gfx::layout_t<attributes...> layout)
        {
            _->tie(buffer->handle(), layout);
        }
        void tie(std::shared_ptr<gfx::IndexBuffer>     buffer                                     )
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
