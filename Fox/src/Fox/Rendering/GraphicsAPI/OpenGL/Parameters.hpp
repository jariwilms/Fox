#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/GraphicsAPI/OpenGL/Types.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Flags.hpp"

namespace fox::gfx::api::gl
{
    template<typename T>
    struct color_t
    {
        using vector_t = glm::vec<4, T, glm::packed_highp>;

        gl::enum_t       buffer{};
        gl::Vector<T, 4> value{};
    };
    struct depth_t
    {
        gl::float32_t value{};
    };
    struct stencil_t
    {
        gl::int32_t value{};
    };
    struct depthstencil_t
    {
        gl::float32_t dValue{};
        gl::int32_t   sValue{};
    };

    using FT = glf::Texture;

    using TextureParameter = std::variant<FT::MinificationFilter, FT::MagnificationFilter, FT::Wrapping>;
    using ClearValue       = std::variant<color_t<gl::int32_t>, color_t<gl::uint32_t>, color_t<gl::float32_t>, depth_t, stencil_t, depthstencil_t>;
}