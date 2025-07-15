#pragma once

#include <fox/rendering/api/opengl/core/flags.hpp>

import std;
import fox.rendering.api.opengl.types;

namespace fox::gfx::api::gl
{
    struct message_log
    {
        gl ::uint32_t        id      {};
        std::string          message {};
        glf::Debug::Source   source  {};
        glf::Debug::Type     type    {};
        glf::Debug::Severity severity{};
    };

    struct binary_info
    {
        gl::enum_t               format{};
        std::vector<gl::uint8_t> binary{}; 
    };

    struct indirect_command
    {
        gl::count_t  count       {};
        gl::count_t  instances   {};
        gl::index_t  index       {};
        gl::int32_t  baseVertex  {};
        gl::uint32_t baseInstance{};
    };
}
