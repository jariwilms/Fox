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
    template<typename Shader>
    static auto shaders_from_binaries(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<Shader>, 2>
        {
            gfx::Shader::create(gfx::Shader::Stage::Vertex,   *vertexFile  ->read()), 
            gfx::Shader::create(gfx::Shader::Stage::Fragment, *fragmentFile->read()), 
        };
    }
    template<typename Shader>
    static auto shaders_from_binaries(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& geometryFile = io::load(geometry);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<Shader>, 3>
        {
            gfx::Shader::create(gfx::Shader::Stage::Vertex,   *vertexFile  ->read()), 
            gfx::Shader::create(gfx::Shader::Stage::Geometry, *geometryFile->read()),
            gfx::Shader::create(gfx::Shader::Stage::Fragment, *fragmentFile->read()), 
        };
    }
}
