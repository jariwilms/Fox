#pragma once

#include "stdafx.hpp"

#include "Helix/IO/Filesystem/File.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/Rendering.hpp"

namespace hlx::gfx
{
    auto shaders_from_source()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    auto shaders_from_binaries(std::string_view vertex, std::string_view fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<Shader>, 2>
        {
            std::make_shared<Shader>(Shader::Stage::Vertex,   *vertexFile->read()), 
            std::make_shared<Shader>(Shader::Stage::Fragment, *fragmentFile->read()), 
        };
    }
}
