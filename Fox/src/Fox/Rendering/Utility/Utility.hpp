#pragma once

#include "stdafx.hpp"

#include "Fox/IO/Filesystem/File.hpp"
#include "Fox/IO/IO.hpp"
#include "Fox/Rendering/Rendering.hpp"

namespace fox::gfx::api
{
    auto shaders_from_source()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    template<typename SHADER_T>
    auto shaders_from_binaries(std::string_view vertex, std::string_view fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<SHADER_T>, 2>
        {
            std::make_shared<SHADER_T>(Shader::Stage::Vertex,   *vertexFile->read()), 
            std::make_shared<SHADER_T>(Shader::Stage::Fragment, *fragmentFile->read()), 
        };
    }
}
