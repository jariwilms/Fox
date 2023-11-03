#pragma once

#include "stdafx.hpp"

#include "Helix/IO/Filesystem/File.hpp"
#include "Helix/Rendering/Rendering.hpp"

namespace hlx::gfx
{
    //auto shaders_from_source()
    //{
    //    throw std::logic_error{ "The method or operation has not been implemented!" };
    //}
    auto shaders_from_binaries(std::string_view vertex, std::string_view fragment)
    {
        auto vertexFile   = File{ vertex };
        auto fragmentFile = File{ fragment };

        return std::array<Shader, 2>
        {
            Shader{ Shader::Stage::Vertex,   *vertexFile.read() },
            Shader{ Shader::Stage::Fragment, *fragmentFile.read() },
        };
    }
}
