export module fox.io.loading;

import std;
import fox.core.image;
import fox.io.filesystem.directory;
import fox.io.filesystem.entry;
import fox.io.filesystem.file;
import fox.rendering.texture;

export namespace fox::io
{
    enum class e_asset
    {
        file,
        image,
        //texture1d,
        texture2d,
        //texture3d,
        //shader, 
        //model, 
    };

    const io::directory root{ FOX_ASSET_DIR };

    template<io::e_asset A = io::e_asset::file, typename... Args>
    auto load(const std::filesystem::path& path, Args&&... args)
    {
        auto absolute       = path.is_absolute() ? path : root / path;
        auto load_file      = [&](const std::filesystem::path& path) -> std::shared_ptr<io::file>
            {
                return std::make_shared<io::file>(path);
            };
        auto load_image     = [&](const std::filesystem::path& path, fox::image::format_e format) -> fox::image
            {
                return fox::image::decode(format, *load_file(path)->read());
            };
        auto load_texture2d = [&](const std::filesystem::path& path) -> std::shared_ptr<gfx::texture2d>
            {
                auto image = load_image(path, fox::image::format_e::rgba8);
                return gfx::texture2d::create(gfx::texture2d::e_format::RGBA8_UNORM, image.dimensions(), image.data());
            };

        using enum io::e_asset;
        if constexpr (A == file     ) return std::invoke(load_file     , absolute, std::forward<Args>(args)...);
        if constexpr (A == image    ) return std::invoke(load_image    , absolute, std::forward<Args>(args)...);
        if constexpr (A == texture2d) return std::invoke(load_texture2d, absolute, std::forward<Args>(args)...);
    }
}
