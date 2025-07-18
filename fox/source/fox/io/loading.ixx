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
        Texture1D,
        Texture2D,
        Texture3D,
        Shader, 
        Model, 
    };

    inline const io::Directory root{ FOX_ASSET_DIR };

    template<Asset A = Asset::File, typename... Args>
    inline auto _load(const std::filesystem::path& path, Args... args) = delete;

    template<> inline auto _load<io::Asset::File>     (const std::filesystem::path& path)
    {
        return std::make_shared<io::File>(path);
    }
    template<> inline auto _load<io::Asset::Image>    (const std::filesystem::path& path, fox::Image::Format format)
    {
        const auto& file  = io::_load(path);
        const auto& data  = file->read();
        const auto& image = fox::Image::decode(format, *data);
        
        return image;
    }
    template<> inline auto _load<io::Asset::Texture2D>(const std::filesystem::path& path)
    {
        const auto& image = io::_load<io::Asset::Image>(path, fox::Image::Format::RGBA8);

        return gfx::Texture2D::create(gfx::Texture2D::Format::RGBA8_UNORM, image.dimensions(), image.data());
    }

    template<Asset A = Asset::File, typename... Args>
    inline auto load(const std::filesystem::path& path, Args... args)
    {
        return _load<A>(path.is_absolute() ? path : root / path, args...);
    }
}
