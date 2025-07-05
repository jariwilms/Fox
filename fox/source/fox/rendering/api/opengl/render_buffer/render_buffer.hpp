#pragma once

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/render_buffer/render_buffer.hpp>

namespace fox::gfx::api::gl
{
    class RenderBuffer : public gl::Object
    {
    public:
        using Format = api::RenderBuffer::Format;

         RenderBuffer(Format format, const gl::Vector2u& dimensions)
            : format_{ format }, dimensions_{ dimensions }
        {
            handle_ = gl::create_render_buffer();

            gl::render_buffer_storage(handle_, gl::map_render_buffer_format(format), dimensions_);
        }
         RenderBuffer(RenderBuffer&&) noexcept = default;
        ~RenderBuffer()
        {
            gl::delete_render_buffer(handle_);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            if (dimensions == dimensions_) return;

            this->operator=(RenderBuffer{ format_, dimensions_ });
        }

        auto format    () const -> Format
        {
            return format_;
        }
        auto dimensions() const -> const gl::Vector2u&
        {
            return dimensions_;
        }

        auto operator=(RenderBuffer&&) noexcept -> RenderBuffer& = default;

    private:
        Format       format_    ;
        gl::Vector2u dimensions_;
    };
    class RenderBufferMultisample : public gl::Object
    {
    public:
        using Format = api::RenderBuffer::Format;

         RenderBufferMultisample(Format format, const gl::Vector2u& dimensions, gl::uint32_t samples)
            : format_{ format }, dimensions_{ dimensions }, samples_{ samples }
        {
            handle_ = gl::create_render_buffer();

            gl::render_buffer_storage_multisample(handle_, gl::map_render_buffer_format(format), dimensions_, samples_);
        }
         RenderBufferMultisample(RenderBufferMultisample&&) noexcept = default;
        ~RenderBufferMultisample()
        {
            gl::delete_render_buffer(handle_);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            if (dimensions == dimensions_) return;

            this->operator=(RenderBufferMultisample{ format_, dimensions, samples_ });
        }

        auto format    () const -> Format
        {
            return format_;
        }
        auto dimensions() const -> const gl::Vector2u&
        {
            return dimensions_;
        }
        auto samples   () const -> gl::uint32_t
        {
            return samples_;
        }

        auto operator=(RenderBufferMultisample&&) noexcept -> RenderBufferMultisample& = default;

    private:
        Format       format_    ;
        gl::Vector2u dimensions_;
        gl::uint32_t samples_   ;
    };
}
