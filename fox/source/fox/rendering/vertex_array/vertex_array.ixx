export module fox.rendering.vertex_array;

import std;
import fox.core.types;
import fox.core.meta;
import fox.rendering.api;
import fox.rendering.layout;
import fox.rendering.buffer;

export namespace fox::gfx
{
    class vertex_array
    {
    public:
        explicit vertex_array(std::shared_ptr<impl::VertexArray> _)
            : _{ _ } {}

        static auto create() -> std::shared_ptr<gfx::vertex_array>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::vertex_array>>(std::in_place_t{});
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

        template<typename T, typename... Attributes>
        void tie(std::shared_ptr<gfx::VertexBuffer<T>> buffer, gfx::vertex_layout<Attributes...> layout)
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
        vertex_array()
            : _{ std::make_shared<impl::VertexArray>() } {}

    private:
        std::shared_ptr<impl::VertexArray> _;
    };
}
