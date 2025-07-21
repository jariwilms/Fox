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
    class FrameBuffer
    {
    public:
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;
        using Surface       = api::FrameBuffer::Surface;
        using Target        = api::FrameBuffer::Target;

        explicit FrameBuffer(std::shared_ptr<impl::FrameBuffer> _)
            : _{ _ } {}

        static auto create(const fox::Vector2u& dimensions, std::span<const Specification> specifications) -> std::shared_ptr<gfx::FrameBuffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::FrameBuffer>>(std::in_place_t{}, dimensions, specifications);
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, gfx::binding_t binding)
        {
            _->bind_surface<A>(identifier, static_cast<impl::binding_t>(binding));
        }

        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::Texture2D>    texture, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, texture->impl(), level);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::Cubemap>      cubemap, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, cubemap->impl(), level);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::RenderBuffer> renderBuffer)
        {
            _->attach(identifier, attachment, renderBuffer->impl());
        }

        template<Surface A = Surface::Texture>
        void detach(const std::string& identifier, Attachment attachment)
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

        void resize(const fox::Vector2u& dimensions)
        {
            _->resize(dimensions);
        }

        template<Surface A = Surface::Texture>
        auto surface   (const std::string& identifier)
        {
            if constexpr (A == Surface::Texture     ) return std::make_shared<gfx::Texture2D>   (_->surface<A>(identifier));
            if constexpr (A == Surface::Cubemap     ) return std::make_shared<gfx::Cubemap>     (_->surface<A>(identifier));
            if constexpr (A == Surface::RenderBuffer) return std::make_shared<gfx::RenderBuffer>(_->surface<A>(identifier));
        }
        auto attachment(Attachment attachment) -> std::string
        {
            return _->attachment(attachment);
        }
        
        auto dimensions() const -> const fox::Vector2u&
        {
            return _->dimensions();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::FrameBuffer>
        {
            return _;
        }

    protected:
        FrameBuffer(const fox::Vector2u& dimensions, std::span<const Specification> specifications)
            : _{ std::make_shared<impl::FrameBuffer>(dimensions, specifications) } {}

    private:
        std::shared_ptr<impl::FrameBuffer> _;
    };
    class FrameBufferMultisample
    {
    public:
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::SpecificationMultisample;
        using Surface       = api::FrameBuffer::Surface;
        using Target        = api::FrameBuffer::Target;

        explicit FrameBufferMultisample(std::shared_ptr<impl::FrameBufferMultisample> _)
            : _{ _ } {}

        static auto create(const fox::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples) -> std::shared_ptr<gfx::FrameBufferMultisample>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::FrameBufferMultisample>>(std::in_place_t{}, dimensions, specifications, samples);
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, gfx::binding_t binding)
        {
            _->bind_surface<A>(identifier, static_cast<impl::binding_t>(binding));
        }

        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::Texture2DMultisample>    texture, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, texture->impl(), level);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::RenderBufferMultisample> renderBuffer)
        {
            _->attach(identifier, attachment, renderBuffer->impl());
        }

        template<Surface A = Surface::Texture>
        void detach(const std::string& identifier, Attachment attachment)
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

        void resize(const fox::Vector2u& dimensions)
        {
            _->resize(dimensions);
        }

        template<Surface A = Surface::Texture>
        auto surface   (const std::string& identifier)
        {
            if constexpr (A == Surface::Texture)      return std::make_shared<gfx::Texture2D>   (_->surface<A>(identifier));
            if constexpr (A == Surface::Cubemap)      return std::make_shared<gfx::Cubemap>     (_->surface<A>(identifier));
            if constexpr (A == Surface::RenderBuffer) return std::make_shared<gfx::RenderBuffer>(_->surface<A>(identifier));
        }
        auto attachment(Attachment attachment) -> std::string
        {
            return _->attachment(attachment);
        }

        auto dimensions() const -> const fox::Vector2u&
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
        auto impl      () const -> std::shared_ptr<impl::FrameBufferMultisample>
        {
            return _;
        }

    protected:
        FrameBufferMultisample(const fox::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples)
            : _{ std::make_shared<impl::FrameBufferMultisample>(dimensions, specifications, samples) } {}

    private:
        std::shared_ptr<impl::FrameBufferMultisample> _;
    };
}
