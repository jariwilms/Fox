export module fox.io.loading;

import std;
import fox.core.image;
import fox.io.filesystem.directory;
import fox.io.filesystem.entry;
import fox.io.filesystem.file;
import fox.rendering.texture;

export namespace fox::io
{
    enum class Asset
    {
        File,
        Image,
        //Texture1D,
        Texture2D,
        //Texture3D,
        //Shader, 
        //Model, 
    };

    const io::directory root{ FOX_ASSET_DIR };

    template<Asset A = Asset::File, typename... Args>
    auto load(const std::filesystem::path& path, Args&&... args)
    {
        auto absolute       = path.is_absolute() ? path : root / path;
        auto load_file      = [&](const std::filesystem::path& path) -> std::shared_ptr<io::file>
            {
                return std::make_shared<io::file>(path);
            };
        auto load_image     = [&](const std::filesystem::path& path, fox::image::e_format format) -> fox::image
            {
                return fox::image::decode(format, *load_file(path)->read());
            };
        auto load_texture2d = [&](const std::filesystem::path& path) -> std::shared_ptr<gfx::Texture2D>
            {
                auto image = load_image(path, fox::image::e_format::rgba8);
                return gfx::Texture2D::create(gfx::Texture2D::Format::RGBA8_UNORM, image.dimensions(), image.data());
            };

        if constexpr (A == io::Asset::File     ) return std::invoke(load_file     , absolute, std::forward<Args>(args)...);
        if constexpr (A == io::Asset::Image    ) return std::invoke(load_image    , absolute, std::forward<Args>(args)...);
        if constexpr (A == io::Asset::Texture2D) return std::invoke(load_texture2d, absolute, std::forward<Args>(args)...);
    }
}
