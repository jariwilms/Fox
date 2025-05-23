#pragma once

#include "stdafx.hpp"

#include "Filesystem/File.hpp"
#include "Filesystem/Directory.hpp"
#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::io
{
    enum class Asset
    {
        File,
        Image,
        Texture1D,
        Texture2D,
        Texture3D,
        Shader, 
        Model, 
    };

    static inline const fox::Directory root{ FOX_ASSET_DIR };

    template<Asset A = Asset::File, typename... Args>
    static auto _load(const std::filesystem::path& path, Args... args) = delete;

    template<> static auto _load<io::Asset::File>     (const std::filesystem::path& path)
    {
        return std::make_shared<io::File>(path);
    }
    template<> static auto _load<io::Asset::Image>    (const std::filesystem::path& path, fox::Image::Format format)
    {
        const auto& file = io::_load(path);
        const auto& data = file->read();
        const auto& image = fox::Image::decode(format, *data);

        return image;
    }
    template<> static auto _load<io::Asset::Texture2D>(const std::filesystem::path& path)
    {
        const auto& image = io::_load<io::Asset::Image>(path, fox::Image::Format::RGBA8);

        return gfx::Texture2D::create(gfx::Texture2D::Format::RGBA8_UNORM, image.dimensions(), image.data());
    }

    template<Asset A = Asset::File, typename... Args>
    static auto load(const std::filesystem::path& path, Args... args)
    {
        return _load<A>(path.is_absolute() ? path : root / path, args...);
    }
}
