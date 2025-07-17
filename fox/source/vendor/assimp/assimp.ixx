module;

#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

export module vendor.assimp;
export import :types;

import std;
import fox.core.enumeration;
import fox.core.types;

auto importer = assimp::importer{};

export namespace assimp
{
    auto read_file        (const std::filesystem::path& path, processing_flags flags) -> assimp::scene
    {
        const auto* aiScene = ::importer.ReadFile(path.string(), std::to_underlying(flags));

        if (!aiScene                                                              ) throw std::runtime_error{ "Failed to create scene!" };
        if (!aiScene->mFlags & std::to_underlying(assimp::scene_flags::incomplete)) throw std::runtime_error{ "Scene is incomplete!"    };
        if (!aiScene->mRootNode                                                   ) throw std::runtime_error{ "Scene has no root node!" };

        return assimp::scene{ aiScene };
    }
    auto load_scene       (const std::filesystem::path& path) -> assimp::scene
    {
        return read_file(path, 
            assimp::processing_flags::calculate_tangent_space  | 
            assimp::processing_flags::find_invalid_data        | 
            assimp::processing_flags::fix_in_facing_normals    | 
            assimp::processing_flags::generate_bounding_boxes  | 
            assimp::processing_flags::generate_smooth_normals  | 
            assimp::processing_flags::generate_uv_coordinates  | 
            assimp::processing_flags::improve_cache_locality   | 
            assimp::processing_flags::join_identical_vertices  | 
            assimp::processing_flags::optimize_graph           | 
            assimp::processing_flags::optimize_meshes          | 
            assimp::processing_flags::sort_by_primitive_type   | 
            assimp::processing_flags::split_large_meshes       | 
            assimp::processing_flags::transform_uv_coordinates | 
            assimp::processing_flags::triangulate              );
    }
    auto get_texture      (const assimp::material& material, assimp::texture_type type, fox::uint32_t mapping = 0u) -> std::optional<std::string>
    {
        auto name   = assimp::string{};
        auto result = static_cast<assimp::result>(material.GetTexture(static_cast<aiTextureType>(type), mapping, &name));

        if   (result == assimp::result::success) return std::string{ name.C_Str() };
        else                                     return std::nullopt;
    }
    auto get_texture_count(const assimp::material& material, assimp::texture_type type) -> fox::uint32_t
    {
        return material.GetTextureCount(static_cast<aiTextureType>(type));
    }
}
