#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/IO/IO.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api
{
    static auto shaders_from_source()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    template<typename Shader>
    static auto shaders_from_binaries(std::string_view vertex, std::string_view fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<Shader>, 2>
        {
            std::make_shared<Shader>(Shader::Stage::Vertex,   *vertexFile->read()), 
            std::make_shared<Shader>(Shader::Stage::Fragment, *fragmentFile->read()), 
        };
    }
    static auto texture_from_file(const std::filesystem::path& path)
    {
        const auto& file  = io::load(path);
        const auto& data  = file->read();
        const auto& image = fox::Image::decode(fox::Image::Layout::RGBA8, *data);
        
        return std::make_shared<gfx::Texture2D>(gfx::Texture2D::Format::RGBA8_UNORM, image.dimensions(), image.data());
    }
}
