export module fox.rendering.api.opengl.buffer;

import std;
import fox.rendering.api.opengl;
import fox.rendering.base.buffer;

export namespace fox::gfx::api::gl
{
    template<typename T>
    class buffer : public gl::object
    {
    public:
        explicit buffer(gl::count_t count)
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::size_t>(count * sizeof(T)) }, range_{}, locks_{}, data_{}
        {
            gl::buffer_storage<T>(
                handle_                                     ,
                gl::buffer_storage_flags_e::dynamic_storage |
                gl::buffer_storage_flags_e::read_write      |
                gl::buffer_storage_flags_e::persistent      |
                gl::buffer_storage_flags_e::coherent        ,
                count                                       );
        }
        explicit buffer(std::span<const T> data)
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::size_t>(data.size_bytes()) }, range_{}, locks_{}, data_{}
        {
            gl::buffer_storage<T>(
                handle_                                     , 
                gl::buffer_storage_flags_e::dynamic_storage |
                gl::buffer_storage_flags_e::read_write      |
                gl::buffer_storage_flags_e::persistent      |
                gl::buffer_storage_flags_e::coherent        ,
                data                                        );
        }

        void copy      (                   std::span<const T> data)
        {
            if (gl::compare<std::greater>(data.size_bytes(), size())) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_data(handle_, gl::index_t{ 0u }, data);
        }
        void copy_range(gl::index_t index, std::span<const T> data)
        {
            if (gl::compare<std::greater_equal>(index, count())) throw std::invalid_argument{ "Index out of range!" };

            gl::buffer_data(handle_, index, data);
        }

        auto map      () -> std::weak_ptr<std::span<T>>
        {
            unmap();

            auto span = gl::map_buffer_range<T>(
                handle_                                             , 
                gl::buffer_mapping_range_access_flags_e::read_write | 
                gl::buffer_mapping_range_access_flags_e::persistent | 
                gl::buffer_mapping_range_access_flags_e::coherent   , 
                count()                                             );

            data_  = std::shared_ptr<std::span<T>>{ span, [this](auto* _) { unmap(); } };
            range_ = count();

            return data_;
        }
        auto map_range(gl::range range) -> std::weak_ptr<std::span<T>>
        {
            unmap();

            range.count = std::min(range.count, count()              );
            range.index = std::min(range.index, count() - range.count);

            auto span = gl::map_buffer_range<T>(
                handle_                                                , 
                gl::buffer_mapping_range_access_flags_e::read_write    | 
                gl::buffer_mapping_range_access_flags_e::persistent    | 
                gl::buffer_mapping_range_access_flags_e::coherent      | 
                gl::buffer_mapping_range_access_flags_e::flush_explicit, 
                range                                                  );

            data_  = std::shared_ptr<std::span<T>>{ span, [this](const auto* _) { unmap(); } };
            range_ = range;
            
            return data_;
        }
        auto is_mapped() const -> gl::bool_t
        {
            return data_.operator bool();
        }
        void unmap    ()
        {
            if (!is_mapped()) return;

            data_ .reset();
            locks_.clear();
            
            if (!gl::unmap_buffer(handle_)) throw std::runtime_error{ "Data store is undefined!" };
        }

        void lock_range (gl::range range)
        {
            range.count = std::min(range.count, count()              );
            range.index = std::min(range.index, count() - range.count);

            locks_.emplace_back(range, gl::fence_sync());
        }
        void await_range(gl::range range)
        {
            auto locks = std::vector<gl::lock_t>{};

            std::ranges::for_each(locks_, [&](const gl::lock_t& _)
                {
                    const auto& [lock, sync] = _;
                    
                    if   (gl::range_overlaps(range, lock))
                    {
                        auto command = gl::synchronization_command_e::none;
                        auto time    = gl::time_t{};

                        while (gl::True)
                        {
                            auto status = gl::client_wait_sync(sync, command, time);

                            if (status == gl::synchronization_status_e::already_signaled   ) break;
                            if (status == gl::synchronization_status_e::condition_satisfied) break;
                            if (status == gl::synchronization_status_e::wait_failed        ) throw std::runtime_error{ "An error occurred!" };

                            command = gl::synchronization_command_e::flush;
                            time    = static_cast<gl::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count());
                        }

                        gl::delete_sync(sync);
                    }
                    else
                    {
                        locks.emplace_back(lock, sync);
                    }
                });

            locks_ = std::move(locks);
        }

        auto size () const -> gl::size_t
        {
            return size_;
        }
        auto count() const -> gl::count_t
        {
            return static_cast<gl::count_t>(size() / sizeof(T));
        }
        auto data () const -> std::weak_ptr<std::span<const T>>
        {
            return data_;
        }
        auto data () -> std::weak_ptr<std::span<T>>
        {
            return data_;
        }

    private:
        gl::size_t                    size_;
        gl::range                     range_;
        std::vector<gl::lock_t>       locks_;
        std::shared_ptr<std::span<T>> data_;
    };
    template<typename T>
    class uniform_buffer : public gl::object
    {
    public:
        explicit uniform_buffer(const T& data = {})
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ sizeof(T) }
        {
            gl::buffer_storage<T>(
                handle_                                    , 
                gl::buffer_storage_flags_e::dynamic_storage, 
                std::span<const T>{ &data, 1u }            );
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_buffer_base(handle_, gl::buffer_base_target_e::uniform_buffer, binding);
        }

        void copy      (const T& data)
        {
            gl::buffer_data(handle_, gl::index_t{ 0u }, std::span<const T>{ &data, 1u });
        }
        template<typename... T>
        void copy_slice(gl::offset_t offset, const std::tuple<T...>& data)
        {
            auto slice = std::array<gl::byte_t, (sizeof(T) + ... + 0u)>{};
            if (gl::compare<std::greater>(offset + slice.size(), size())) throw std::range_error{ "The given data is too large!" };

            std::apply([&slice](const auto&... element)
                {
                    auto offset = gl::offset_t{};
                    ((std::memcpy(slice.data() + offset, &element, sizeof(element)), offset += sizeof(element)), ...);
                }, data);

            gl::buffer_data<gl::byte_t>(handle_, static_cast<gl::index_t>(offset), slice);
        }

        auto size() const -> gl::size_t
        {
            return size_;
        }

    private:
        gl::size_t size_;
    };
    template<typename T, gl::count_t N>
    class uniform_array_buffer : public gl::object
    {
    public:
        explicit uniform_array_buffer()
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::size_t>(N * sizeof(T)) }, range_{}, locks_{}, data_{}
        {
            gl::buffer_storage<T>(
                handle_, 
                gl::buffer_storage_flags_e::dynamic_storage | 
                gl::buffer_storage_flags_e::read_write      |
                gl::buffer_storage_flags_e::persistent      | 
                gl::buffer_storage_flags_e::coherent        , 
                gl::size_t{ N * sizeof(T) }                 );
        }
        explicit uniform_array_buffer(std::span<const T> data)
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::size_t>(data.size_bytes()) }, range_{}, locks_{}, data_{}
        {
            gl::buffer_storage<T>(
                handle_                                     , 
                gl::buffer_storage_flags_e::dynamic_storage |
                gl::buffer_storage_flags_e::read_write      |
                gl::buffer_storage_flags_e::persistent      | 
                gl::buffer_storage_flags_e::coherent        , 
                data                                        );
        }

        void bind      (gl::binding_t binding) const
        {
            gl::bind_buffer_base(handle_, gl::buffer_base_target_e::uniform_buffer, binding);
        }
        void bind_range(gl::binding_t binding, gl::range range) const
        {
            gl::bind_buffer_range<T>(handle_, gl::buffer_base_target_e::uniform_buffer, binding, range);
        }

        void copy      (std::span<const T, N> data)
        {
            gl::buffer_data(handle_, gl::offset_t{ 0u }, std::span<const T>{ data });
        }
        void copy_index(gl::index_t index, const T& data)
        {
            gl::buffer_data(handle_, index, std::span<const T>{ &data, 1u });
        }
        void copy_range(gl::index_t index, std::span<const T> data)
        {
            gl::buffer_data(handle_, index, data);
        }

        auto map      () -> std::weak_ptr<std::span<T>>
        {
            unmap();

            auto span = gl::map_buffer_range<T>(
                handle_, 
                gl::buffer_mapping_range_access_flags_e::read_write |
                gl::buffer_mapping_range_access_flags_e::persistent |
                gl::buffer_mapping_range_access_flags_e::coherent   ,
                count()                                             );

            data_  = std::shared_ptr<std::span<T>>{ span, [this](const auto* _) { unmap(); } };
            range_ = count();

            return data_;
        }
        auto map_range(gl::range range) -> std::weak_ptr<std::span<T>>
        {
            unmap();

            range.count = std::min(range.count, count()              );
            range.index = std::min(range.index, count() - range.count);

            auto span = gl::map_buffer_range<T>(
                handle_                                                ,
                gl::buffer_mapping_range_access_flags_e::read_write    |
                gl::buffer_mapping_range_access_flags_e::persistent    |
                gl::buffer_mapping_range_access_flags_e::coherent      |
                gl::buffer_mapping_range_access_flags_e::flush_explicit,
                range                                                  );

            data_  = std::shared_ptr<std::span<T>>{ span, [this](const auto* _) { unmap(); } };
            range_ = range;

            return data_;
        }
        auto is_mapped() const -> gl::bool_t
        {
            return data_.operator bool();
        }
        void unmap    ()
        {
            if (!is_mapped()) return;

            data_ .reset();
            locks_.clear();

            if (!gl::unmap_buffer(handle_)) throw std::runtime_error{ "Data store is undefined!" };

        }

        void lock_range (gl::range range)
        {
            range.count = std::min(range.count, count()              );
            range.index = std::min(range.index, count() - range.count);

            locks_.emplace_back(range, gl::fence_sync());
        }
        void await_range(gl::range range)
        {
            auto locks = std::vector<gl::lock_t>{};

            std::ranges::for_each(locks_, [&](const gl::lock_t& _)
                {
                    const auto& [lock, sync] = _;

                    if (gl::range_overlaps(range, lock))
                    {
                        auto command = gl::synchronization_command_e::none;
                        auto time    = gl::time_t{};

                        while (gl::True)
                        {
                            auto status = gl::client_wait_sync(sync, command, time);

                            if (status == gl::synchronization_status_e::already_signaled   ) break;
                            if (status == gl::synchronization_status_e::condition_satisfied) break;
                            if (status == gl::synchronization_status_e::wait_failed        ) throw std::runtime_error{ "An error occurred!" };

                            command = gl::synchronization_command_e::flush;
                            time    = static_cast<gl::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count());
                        }

                        gl::delete_sync(sync);
                    }
                    else
                    {
                        locks.emplace_back(lock, sync);
                    }
                });

            locks_ = std::move(locks);
        }

        auto size () const
        {
            return size_;
        }
        auto count() const
        {
            return N;
        }
        auto data () const -> std::weak_ptr<std::span<const T>>
        {
            return data_;
        }
        auto data () -> std::weak_ptr<std::span<T>>
        {
            return data_;
        }

    private:
        gl::size_t                    size_;
        gl::range                     range_;
        std::vector<gl::lock_t>       locks_;
        std::shared_ptr<std::span<T>> data_;
    };
}
