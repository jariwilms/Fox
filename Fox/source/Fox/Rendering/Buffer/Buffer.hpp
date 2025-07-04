#pragma once

#include <fox/rendering/api/api.hpp>

namespace fox::gfx
{
    template<typename T>
    class VertexBuffer
    {
    public:
        static inline auto create(std::span<const T> data)
        {
            return std::shared_ptr<const VertexBuffer>(new VertexBuffer{ data });
        }
        static inline auto create(fox::count_t count)
        {
            return std::shared_ptr<const VertexBuffer>(new VertexBuffer{ count });
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

        std::shared_ptr<impl::VertexBuffer<T>> _;
    };
    class IndexBuffer
    {
    public:
        static inline auto create(std::span<const fox::uint32_t> data)
        {
            return std::shared_ptr<const IndexBuffer>(new IndexBuffer{ data });
        }
        static inline auto create(fox::count_t count)
        {
            return std::shared_ptr<const IndexBuffer>(new IndexBuffer{ count });
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
        IndexBuffer(std::span<const fox::index_t> data)
            : _{ std::make_shared<impl::IndexBuffer>(data) } {}
        IndexBuffer(fox::count_t count)
            : _{ std::make_shared<impl::IndexBuffer>(count) } {}

        std::shared_ptr<impl::IndexBuffer> _;
    };

    template<typename T>
    class UniformBuffer
    {
    public:
        static inline auto create(const T& data = {})
        {
            return std::shared_ptr<UniformBuffer>(new UniformBuffer{ data });
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy    (const T& data)
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
        auto impl()   const -> std::shared_ptr<impl::UniformBuffer<T>>
        {
            return _;
        }

    protected:
        UniformBuffer(const T& data = {})
            : _{ std::make_shared<impl::UniformBuffer<T>>(data) } {}

        std::shared_ptr<impl::UniformBuffer<T>> _;
    };
    template<typename T, fox::count_t N>
    class UniformArrayBuffer
    {
    public:
        static inline auto create()
        {
            return std::shared_ptr<UniformArrayBuffer>(new UniformArrayBuffer{});
        }
        static inline auto create(std::span<const T> data)
        {
            return std::shared_ptr<UniformArrayBuffer>(new UniformArrayBuffer{ data });
        }

        void bind      (gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }
        void bind_range(gfx::binding_t binding, fox::range_t range) const
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
        UniformArrayBuffer(std::span<const T> data)
            : _{ std::make_shared<impl::UniformArrayBuffer<T, N>>(data) } {}

        std::shared_ptr<impl::UniformArrayBuffer<T, N>> _;
    };
}
