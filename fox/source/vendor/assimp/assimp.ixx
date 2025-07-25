export module vendor.assimp;
export import :types;

import std;
import <assimp/importer.hpp>;
import <assimp/postprocess.h>;
import <assimp/scene.h>;
import fox.core.types;

auto importer = assimp::importer{};

export namespace assimp
{
    auto read_file        (const std::filesystem::path& path, processing_flags_e flags) -> const assimp::scene&
    {
        const auto* aiScene = ::importer.ReadFile(path.string(), std::to_underlying(flags));

        if (!aiScene                                                                ) throw std::runtime_error{ "Failed to create scene!" };
        if (!aiScene->mFlags & std::to_underlying(assimp::scene_flags_e::incomplete)) throw std::runtime_error{ "Scene is incomplete!"    };
        if (!aiScene->mRootNode                                                     ) throw std::runtime_error{ "Scene has no root node!" };

        return *aiScene;
    }
    auto load_scene       (const std::filesystem::path& path) -> const assimp::scene&
    {
        return read_file(path, 
            assimp::processing_flags_e::calculate_tangent_space  | 
            assimp::processing_flags_e::find_invalid_data        | 
            assimp::processing_flags_e::fix_in_facing_normals    | 
            assimp::processing_flags_e::generate_bounding_boxes  | 
            assimp::processing_flags_e::generate_smooth_normals  | 
            assimp::processing_flags_e::generate_uv_coordinates  | 
            assimp::processing_flags_e::improve_cache_locality   | 
            assimp::processing_flags_e::join_identical_vertices  | 
            assimp::processing_flags_e::optimize_graph           | 
            assimp::processing_flags_e::optimize_meshes          | 
            assimp::processing_flags_e::sort_by_primitive_type   | 
            assimp::processing_flags_e::split_large_meshes       | 
            assimp::processing_flags_e::transform_uv_coordinates | 
            assimp::processing_flags_e::triangulate              );
    }
    auto get_texture      (const assimp::material& material, assimp::texture_type_e type, fox::uint32_t mapping = 0u) -> std::optional<std::string>
    {
        auto name   = assimp::string{};
        auto result = static_cast<assimp::result_e>(material.GetTexture(static_cast<aiTextureType>(type), mapping, &name));

        if   (result == assimp::result_e::success) return std::string{ name.C_Str() };
        else                                       return std::nullopt;
    }
    auto get_texture_count(const assimp::material& material, assimp::texture_type_e type) -> fox::uint32_t
    {
        return material.GetTextureCount(static_cast<aiTextureType>(type));
    }
}
