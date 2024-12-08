#pragma once

#include "stdafx.hpp"

#include "Fox/IO/IO.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api
{
    static auto shaders_from_source()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    template<typename SHADER_T>
    static auto shaders_from_binaries(std::string_view vertex, std::string_view fragment)
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
