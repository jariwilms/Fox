#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Buffer/Buffer.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        template<typename T>
        using VertexBuffer        = api::gl::StaticBuffer<api::Buffer::Type::Vertex,  T>;
        using IndexBuffer         = api::gl::StaticBuffer<api::Buffer::Type::Index,   fox::uint32_t>;

        template<typename T>
        using DynamicVertexBuffer = api::gl::DynamicBuffer<api::Buffer::Type::Vertex, T>;
        using DynamicIndexBuffer  = api::gl::DynamicBuffer<api::Buffer::Type::Index,  fox::uint32_t>;

        template<typename T>
        using UniformBuffer       = api::gl::UniformBuffer<T>;
        template<typename T, fox::uint64_t N>
        using UniformArrayBuffer  = api::gl::UniformArrayBuffer<T, N>;
#endif
    }



    template<typename T>
    class VertexBuffer
    {
    public:
        static inline auto create(std::span<const T> data)
        {
            return std::shared_ptr<const VertexBuffer>(new VertexBuffer{ data });
        }

        fox::size_t   size()   const
        {
            return _->size();
        }
        fox::count_t  count()  const
        {
            return _->count();
        }
        gfx::handle_t handle() const
        {
            return _->handle();
        }

        auto impl() const { return _; } //Temporary solution... maybe
        auto impl()       { return _; }

    protected:
        VertexBuffer(std::span<const T> data)
            : _{ std::make_shared<impl::VertexBuffer<T>>(data) } {}

        std::shared_ptr<impl::VertexBuffer<T>> _;
    };
    class IndexBuffer
    {
    public:
        static inline auto create(std::span<const fox::uint32_t> data)
        {
            return std::shared_ptr<const IndexBuffer>(new IndexBuffer{ data });
        }

        fox::size_t   size()   const
        {
            return _->size();
        }
        fox::count_t  count()  const
        {
            return _->count();
        }
        gfx::handle_t handle() const
        {
            return _->handle();
        }

        auto impl() const { return _; }
        auto impl()       { return _; }

    protected:
        IndexBuffer(std::span<const fox::uint32_t> data)
            : _{ std::make_shared<impl::IndexBuffer>(data) } {}

        std::shared_ptr<impl::IndexBuffer> _;
    };
    template<typename T>
    class DynamicVertexBuffer
    {
    public:
        static inline auto create(fox::count_t count)
        {
            return std::shared_ptr<DynamicVertexBuffer>(new DynamicVertexBuffer{ count });
        }
        static inline auto create(std::span<const T> data)
        {
            return std::shared_ptr<DynamicVertexBuffer>(new DynamicVertexBuffer{ data });
        }

        void copy(std::span<const T> data)
        {
            _->copy(data);
        }
        void copy_range(fox::count_t offset, std::span<const T> data)
        {
            _->copy_range(offset, data);
        }

        template<api::Buffer::Access ACCESS = api::Buffer::Access::ReadWrite>
        auto map(std::optional<fox::count_t> elements = {}, std::optional<fox::count_t> offset = {})
        {
            _->map<ACCESS>(elements, offset);
        }
        void unmap()
        {
            _->unmap();
        }

        fox::size_t   size()      const
        {
            return _->size();
        }
        fox::count_t  count()     const
        {
            return _->count();
        }
        fox::bool_t   is_mapped() const
        {
            return _->is_mapped();
        }
        gfx::handle_t handle()    const
        {
            return _->handle();
        }

    protected:
        DynamicVertexBuffer(fox::count_t count)
            : _{ std::make_shared<impl::DynamicVertexBuffer<T>>(count) } {}
        DynamicVertexBuffer(std::span<const T> data)
            : _{ std::make_shared<impl::DynamicVertexBuffer<T>>(data) } {}

        std::shared_ptr<impl::DynamicVertexBuffer<T>> _;
    };
    class DynamicIndexBuffer
    {
    public:
        static inline auto create(fox::count_t count)
        {
            return std::shared_ptr<DynamicIndexBuffer>(new DynamicIndexBuffer{ count });
        }
        static inline auto create(std::span<const fox::uint32_t> data)
        {
            return std::shared_ptr<DynamicIndexBuffer>(new DynamicIndexBuffer{ data });
        }

        void copy(std::span<const fox::uint32_t> data)
        {
            _->copy(data);
        }
        void copy_range(fox::count_t offset, std::span<const fox::uint32_t> data)
        {
            _->copy_range(offset, data);
        }

        template<api::Buffer::Access ACCESS = api::Buffer::Access::ReadWrite>
        auto map(std::optional<fox::count_t> elements = {}, std::optional<fox::count_t> offset = {})
        {
            _->map<ACCESS>(elements, offset);
        }
        void unmap()
        {
            _->unmap();
        }

        fox::size_t   size()      const
        {
            return _->size();
        }
        fox::count_t  count()     const
        {
            return _->count();
        }
        fox::bool_t   is_mapped() const
        {
            return _->is_mapped();
        }
        gfx::handle_t handle()    const
        {
            return _->handle();
        }

    protected:
        DynamicIndexBuffer(fox::count_t count)
            : _{ std::make_shared<impl::DynamicIndexBuffer>(count) } {}
        DynamicIndexBuffer(std::span<const fox::uint32_t> data)
            : _{ std::make_shared<impl::DynamicIndexBuffer>(data) } {}

        std::shared_ptr<impl::DynamicIndexBuffer> _;
    };
    template<typename T>
    class UniformBuffer
    {
    public:
        static inline auto create(const T& data = {})
        {
            return std::shared_ptr<UniformBuffer>(new UniformBuffer{ data });
        }

        void bind_index(fox::uint32_t index) const
        {
            _->bind_index(index);
        }

        void copy(const T& data)
        {
            _->copy(data);
        }
        template<typename... T>
        void copy_sub(fox::size_t offset, const std::tuple<T...>& data)
        {
            _->copy_sub<T...>(offset, data);
        }

        fox::size_t   size()   const
        {
            return _->size();
        }
        gfx::handle_t handle() const
        {
            return _->handle();
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

        void bind_index(fox::uint32_t index) const
        {
            _->bind_index(index);
        }
        void bind_index_range(fox::uint32_t index, fox::count_t count, fox::count_t offset) const
        {
            _->bind_index_range(index, count, offset);
        }

        void copy(std::span<const T, N> data)
        {
            _->copy(data);
        }
        void copy_index(fox::count_t offset, const T& data)
        {
            _->copy_index(offset, data);
        }
        void copy_range(fox::count_t offset, std::span<const T> data)
        {
            _->copy_range(offset, data);
        }

        fox::size_t   size()   const
        {
            return _->size();
        }
        gfx::handle_t handle() const
        {
            return _->handle();
        }

    protected:
        UniformArrayBuffer()
            : _{ std::make_shared<impl::UniformArrayBuffer<T, N>>() } {}
        UniformArrayBuffer(std::span<const T> data)
            : _{ std::make_shared<impl::UniformArrayBuffer<T, N>>(data) } {}

        std::shared_ptr<impl::UniformArrayBuffer<T, N>> _;
    };
}
