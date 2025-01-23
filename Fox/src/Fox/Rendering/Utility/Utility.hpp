#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/IO/IO.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api
{
    static auto image_from_file(const std::filesystem::path& path, fox::Image::Layout layout = fox::Image::Layout::RGBA8)
    {
        const auto& file    = io::load(path);
        const auto& dataptr = file->read();
        const auto& image   = fox::Image::decode(layout, *dataptr);

        return image;
    }
    static auto images_from_files(std::span<std::filesystem::path> paths)
    {
        std::vector<fox::Image> images{};
        images.reserve(paths.size());

        for (const auto& path : paths)
        {
            images.emplace_back(image_from_file(path, fox::Image::Layout::RGB8));
        }

        return images;
    }
    static auto texture_from_file(const std::filesystem::path& path)
    {
        const auto& image = image_from_file(path, fox::Image::Layout::RGBA8);
        
        return std::make_shared<gfx::Texture2D>(gfx::Texture2D::Format::RGBA8_UNORM, image.dimensions(), image.data());
    }
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
    template<typename Shader>
    static auto shaders_from_binaries(std::string_view vertex, std::string_view geometry, std::string_view fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& geometryFile = io::load(geometry);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<Shader>, 3>
        {
            std::make_shared<Shader>(Shader::Stage::Vertex,   *vertexFile->read()), 
            std::make_shared<Shader>(Shader::Stage::Geometry, *geometryFile->read()),
            std::make_shared<Shader>(Shader::Stage::Fragment, *fragmentFile->read()), 
        };
    }
}
