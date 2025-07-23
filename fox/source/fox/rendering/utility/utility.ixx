export module fox.rendering.utility;

import std;
import fox.io;
import fox.rendering.shader;

export namespace fox::gfx::utl
{
    auto shaders_from_source()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    template<typename S>
    auto shaders_from_binaries(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<S>, 2u>
        {
            gfx::shader::create(gfx::shader::stage_e::Vertex,   *vertexFile  ->read()), 
            gfx::shader::create(gfx::shader::stage_e::Fragment, *fragmentFile->read()), 
        };
    }
    template<typename Shader>
    auto shaders_from_binaries(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment)
    {
        const auto& vertexFile   = io::load(vertex);
        const auto& geometryFile = io::load(geometry);
        const auto& fragmentFile = io::load(fragment);

        return std::array<std::shared_ptr<Shader>, 3u>
        {
            gfx::shader::create(gfx::shader::stage_e::Vertex,   *vertexFile  ->read()), 
            gfx::shader::create(gfx::shader::stage_e::Geometry, *geometryFile->read()),
            gfx::shader::create(gfx::shader::stage_e::Fragment, *fragmentFile->read()), 
        };
    }
}
