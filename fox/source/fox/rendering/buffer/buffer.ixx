export module fox.rendering.buffer;

import std;
import fox.core.types;
import fox.core.meta;
import fox.rendering.api;

export namespace fox::gfx
{
    template<typename T>
    class VertexBuffer
    {
    public:
        explicit VertexBuffer(std::shared_ptr<impl::VertexBuffer<T>> _)
            : _{ _ } {}

        static auto create(std::span<const T> data) -> std::shared_ptr<gfx::VertexBuffer<T>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::VertexBuffer<T>>>(std::in_place_t{}, data);
        }
        static auto create(fox::count_t count) -> std::shared_ptr<gfx::VertexBuffer<T>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::VertexBuffer<T>>>(std::in_place_t{}, count);
        }

        auto size  () const -> fox::size_t
        {
            return _->size();
        }
        auto count () const -> fox::count_t
        {
            return _->count();
        }
        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::VertexBuffer<T>>
        {
            return _;
        }

    protected:
        explicit VertexBuffer(std::span<const T> data)
            : _{ std::make_shared<impl::VertexBuffer<T>>(data) } {}
        explicit VertexBuffer(fox::count_t count)
            : _{ std::make_shared<impl::VertexBuffer<T>>(count) } {}

    private:
        std::shared_ptr<impl::VertexBuffer<T>> _;
    };
    class IndexBuffer
    {
    public:
        explicit IndexBuffer(std::shared_ptr<impl::IndexBuffer> _)
            : _{ _ } {}

        static auto create(std::span<const fox::index_t> data) -> std::shared_ptr<gfx::IndexBuffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::IndexBuffer>>(std::in_place_t{}, data);
        }
        static auto create(fox::count_t count) -> std::shared_ptr<gfx::IndexBuffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::IndexBuffer>>(std::in_place_t{}, count);
        }

        auto size  () const -> fox::size_t
        {
            return _->size();
        }
        auto count () const -> fox::count_t
        {
            return _->count();
        }
        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::IndexBuffer>
        {
            return _;
        }

    protected:
        explicit IndexBuffer(std::span<const fox::index_t> data)
            : _{ std::make_shared<impl::IndexBuffer>(data) } {}
        explicit IndexBuffer(fox::count_t count)
            : _{ std::make_shared<impl::IndexBuffer>(count) } {}

    private:
        std::shared_ptr<impl::IndexBuffer> _;
    };
    template<typename T>
    class UniformBuffer
    {
    public:
        explicit UniformBuffer(std::shared_ptr<impl::UniformBuffer<T>> _)
            : _{ _ } {}

        static auto create(const T& data = {}) -> std::shared_ptr<gfx::UniformBuffer<T>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::UniformBuffer<T>>>(std::in_place_t{}, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (const T& data)
        {
            _->copy(data);
        }
        template<typename... T>
        void copy_slice(fox::offset_t offset, const std::tuple<T...>& data)
        {
            _->copy_slice<T...>(offset, data);
        }

        auto size  () const -> fox::size_t
        {
            return _->size();
        }
        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::UniformBuffer<T>>
        {
            return _;
        }

    protected:
        explicit UniformBuffer(const T& data = {})
            : _{ std::make_shared<impl::UniformBuffer<T>>(data) } {}

    private:
        std::shared_ptr<impl::UniformBuffer<T>> _;
    };
    template<typename T, fox::count_t N>
    class UniformArrayBuffer
    {
    public:
        explicit UniformArrayBuffer(std::shared_ptr<impl::UniformArrayBuffer<T, N>> _)
            : _{ _ } {}

        static auto create() -> std::shared_ptr<gfx::UniformArrayBuffer<T, N>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::UniformArrayBuffer<T, N>>>(std::in_place_t{});
        }
        static auto create(std::span<const T> data) -> std::shared_ptr<gfx::UniformArrayBuffer<T, N>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::UniformArrayBuffer<T, N>>>(std::in_place_t{}, data);
        }

        void bind      (gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }
        void bind_range(gfx::binding_t binding, fox::range range) const
        {
            _->bind(static_cast<impl::binding_t>(binding), impl::range_t{ range.count, range.index });
        }

        void copy      (std::span<const T, N> data)
        {
            _->copy(data);
        }
        void copy_index(fox::index_t index, const T& data)
        {
            _->copy_index(index, data);
        }
        void copy_range(fox::index_t index, std::span<const T> data)
        {
            _->copy_range(index, data);
        }

        auto size  () const -> fox::size_t
        {
            return _->size();
        }
        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::UniformArrayBuffer<T, N>>
        {
            return _;
        }

    protected:
                 UniformArrayBuffer()
            : _{ std::make_shared<impl::UniformArrayBuffer<T, N>>() } {}
        explicit UniformArrayBuffer(std::span<const T> data)
            : _{ std::make_shared<impl::UniformArrayBuffer<T, N>>(data) } {}

    private:
        std::shared_ptr<impl::UniformArrayBuffer<T, N>> _;
    };
}
