#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/core/flags.hpp>
#include <fox/rendering/api/opengl/core/types.hpp>

namespace fox::gfx::api::gl
{
    struct message_log
    {
        gl::uint32_t         id{};
        std::string          message{};
        glf::Debug::Source   source{};
        glf::Debug::Type     type{};
        glf::Debug::Severity severity{};
    };
    struct indirect_command
    {
        gl::count_t  count{};
        gl::count_t  instances{};
        gl::index_t  index{};
        gl::int32_t  baseVertex{};
        gl::uint32_t baseInstance{};
    };
}
