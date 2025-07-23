export module fox.rendering.buffer;

import std;
import fox.core.types;
import fox.core.meta;
import fox.rendering.api;

export namespace fox::gfx
{
    template<typename T>
    class vertex_buffer
    {
    public:
        explicit vertex_buffer(std::shared_ptr<impl::vertex_buffer<T>> _)
            : _{ _ } {}

        static auto create(std::span<const T> data) -> std::shared_ptr<gfx::vertex_buffer<T>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::vertex_buffer<T>>>(std::in_place_t{}, data);
        }
        static auto create(fox::count_t count) -> std::shared_ptr<gfx::vertex_buffer<T>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::vertex_buffer<T>>>(std::in_place_t{}, count);
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
        auto impl  () const -> std::shared_ptr<impl::vertex_buffer<T>>
        {
            return _;
        }

    protected:
        explicit vertex_buffer(std::span<const T> data)
            : _{ std::make_shared<impl::vertex_buffer<T>>(data) } {}
        explicit vertex_buffer(fox::count_t count)
            : _{ std::make_shared<impl::vertex_buffer<T>>(count) } {}

    private:
        std::shared_ptr<impl::vertex_buffer<T>> _;
    };
    class index_buffer
    {
    public:
        explicit index_buffer(std::shared_ptr<impl::index_buffer> _)
            : _{ _ } {}

        static auto create(std::span<const fox::index_t> data) -> std::shared_ptr<gfx::index_buffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::index_buffer>>(std::in_place_t{}, data);
        }
        static auto create(fox::count_t count) -> std::shared_ptr<gfx::index_buffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::index_buffer>>(std::in_place_t{}, count);
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
        auto impl  () const -> std::shared_ptr<impl::index_buffer>
        {
            return _;
        }

    protected:
        explicit index_buffer(std::span<const fox::index_t> data)
            : _{ std::make_shared<impl::index_buffer>(data) } {}
        explicit index_buffer(fox::count_t count)
            : _{ std::make_shared<impl::index_buffer>(count) } {}

    private:
        std::shared_ptr<impl::index_buffer> _;
    };
    template<typename T>
    class uniform_buffer
    {
    public:
        explicit uniform_buffer(std::shared_ptr<impl::uniform_buffer<T>> _)
            : _{ _ } {}

        static auto create(const T& data = {}) -> std::shared_ptr<gfx::uniform_buffer<T>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::uniform_buffer<T>>>(std::in_place_t{}, data);
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
        auto impl  () const -> std::shared_ptr<impl::uniform_buffer<T>>
        {
            return _;
        }

    protected:
        explicit uniform_buffer(const T& data = {})
            : _{ std::make_shared<impl::uniform_buffer<T>>(data) } {}

    private:
        std::shared_ptr<impl::uniform_buffer<T>> _;
    };
    template<typename T, fox::count_t N>
    class uniform_array_buffer
    {
    public:
        explicit uniform_array_buffer(std::shared_ptr<impl::uniform_array_buffer<T, N>> _)
            : _{ _ } {}

        static auto create() -> std::shared_ptr<gfx::uniform_array_buffer<T, N>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::uniform_array_buffer<T, N>>>(std::in_place_t{});
        }
        static auto create(std::span<const T> data) -> std::shared_ptr<gfx::uniform_array_buffer<T, N>>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::uniform_array_buffer<T, N>>>(std::in_place_t{}, data);
        }

        void bind      (gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }
        void bind_range(gfx::binding_t binding, fox::range range) const
        {
            _->bind(static_cast<impl::binding_t>(binding), impl::range{ range.count, range.index });
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
        auto impl  () const -> std::shared_ptr<impl::uniform_array_buffer<T, N>>
        {
            return _;
        }

    protected:
                 uniform_array_buffer()
            : _{ std::make_shared<impl::uniform_array_buffer<T, N>>() } {}
        explicit uniform_array_buffer(std::span<const T> data)
            : _{ std::make_shared<impl::uniform_array_buffer<T, N>>(data) } {}

    private:
        std::shared_ptr<impl::uniform_array_buffer<T, N>> _;
    };
}
