export module fox.rendering.frame_buffer;

import std;
import fox.core.meta;
import fox.core.types;
import fox.rendering.api;
import fox.rendering.cubemap;
import fox.rendering.texture;
import fox.rendering.render_buffer;
import fox.rendering.base.frame_buffer;

export namespace fox::gfx
{
    class frame_buffer
    {
    public:
        using attachment_e    = api::frame_buffer::Attachment;
        using specification_e = api::frame_buffer::Specification;
        using surface_e       = api::frame_buffer::Surface;
        using target_e        = api::frame_buffer::Target;

        explicit frame_buffer(std::shared_ptr<impl::frame_buffer> _)
            : _{ _ } {}

        static auto create(const fox::vector2u& dimensions, std::span<const specification_e> specifications) -> std::shared_ptr<gfx::frame_buffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::frame_buffer>>(std::in_place_t{}, dimensions, specifications);
        }

        void bind(target_e target)
        {
            _->bind(target);
        }
        template<surface_e A = surface_e::texture>
        void bind_surface(const std::string& identifier, gfx::binding_t binding)
        {
            _->bind_surface<A>(identifier, static_cast<impl::binding_t>(binding));
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gfx::texture2d>    texture, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, texture->impl(), level);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gfx::cubemap>      cubemap, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, cubemap->impl(), level);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gfx::render_buffer> renderBuffer)
        {
            _->attach(identifier, attachment, renderBuffer->impl());
        }

        template<surface_e A = surface_e::texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            _->detach<A>(identifier, attachment);
        }
        
        void read_from(const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->read_from(identifier, static_cast<impl::index_t>(index), level);
        }
        void write_to (const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->write_to(identifier, static_cast<impl::index_t>(index), level);
        }

        void resize(const fox::vector2u& dimensions)
        {
            _->resize(dimensions);
        }

        template<surface_e A = surface_e::texture>
        auto surface   (const std::string& identifier)
        {
            if constexpr (A == surface_e::texture      ) return std::make_shared<gfx::texture2d>    (_->surface<A>(identifier));
            if constexpr (A == surface_e::cubemap      ) return std::make_shared<gfx::cubemap>      (_->surface<A>(identifier));
            if constexpr (A == surface_e::render_buffer) return std::make_shared<gfx::render_buffer>(_->surface<A>(identifier));
        }
        auto attachment(attachment_e attachment) -> std::string
        {
            return _->attachment(attachment);
        }
        
        auto dimensions() const -> const fox::vector2u&
        {
            return _->dimensions();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::frame_buffer>
        {
            return _;
        }

    protected:
        frame_buffer(const fox::vector2u& dimensions, std::span<const specification_e> specifications)
            : _{ std::make_shared<impl::frame_buffer>(dimensions, specifications) } {}

    private:
        std::shared_ptr<impl::frame_buffer> _;
    };
    class frame_buffer_ms
    {
    public:
        using attachment_e    = api::frame_buffer::Attachment;
        using specification_e = api::frame_buffer::SpecificationMultisample;
        using surface_e       = api::frame_buffer::Surface;
        using target_e        = api::frame_buffer::Target;

        explicit frame_buffer_ms(std::shared_ptr<impl::frame_buffer_ms> _)
            : _{ _ } {}

        static auto create(const fox::vector2u& dimensions, std::span<const specification_e> specifications, fox::uint32_t samples) -> std::shared_ptr<gfx::frame_buffer_ms>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::frame_buffer_ms>>(std::in_place_t{}, dimensions, specifications, samples);
        }

        void bind(target_e target)
        {
            _->bind(target);
        }
        template<surface_e A = surface_e::texture>
        void bind_surface(const std::string& identifier, gfx::binding_t binding)
        {
            _->bind_surface<A>(identifier, static_cast<impl::binding_t>(binding));
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gfx::texture2d_ms>    texture, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, texture->impl(), level);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gfx::render_buffer_ms> renderBuffer)
        {
            _->attach(identifier, attachment, renderBuffer->impl());
        }

        template<surface_e A = surface_e::texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            _->detach<A>(identifier, attachment);
        }

        void read_from(const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->read_from(identifier, static_cast<impl::index_t>(index), level);
        }
        void write_to (const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->write_to(identifier, static_cast<impl::index_t>(index), level);
        }

        void resize(const fox::vector2u& dimensions)
        {
            _->resize(dimensions);
        }

        template<surface_e A = surface_e::texture>
        auto surface   (const std::string& identifier)
        {
            if constexpr (A == surface_e::texture      ) return std::make_shared<gfx::texture2d>   (_->surface<A>(identifier));
            if constexpr (A == surface_e::cubemap      ) return std::make_shared<gfx::cubemap>     (_->surface<A>(identifier));
            if constexpr (A == surface_e::render_buffer) return std::make_shared<gfx::render_buffer>(_->surface<A>(identifier));
        }
        auto attachment(attachment_e attachment) -> std::string
        {
            return _->attachment(attachment);
        }

        auto dimensions() const -> const fox::vector2u&
        {
            return _->dimensions();
        }
        auto samples   () const -> fox::uint32_t
        {
            return _->samples();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::frame_buffer_ms>
        {
            return _;
        }

    protected:
        frame_buffer_ms(const fox::vector2u& dimensions, std::span<const specification_e> specifications, fox::uint32_t samples)
            : _{ std::make_shared<impl::frame_buffer_ms>(dimensions, specifications, samples) } {}

    private:
        std::shared_ptr<impl::frame_buffer_ms> _;
    };
}
