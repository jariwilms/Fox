export module vendor.assimp;
export import :types;

import std;
import <assimp/importer.hpp>;
import <assimp/postprocess.h>;
import <assimp/scene.h>;
import fox.core.enumeration;
import fox.core.types;

auto importer = assimp::importer{};

export namespace assimp
{
    auto read_file        (const std::filesystem::path& path, e_processing_flags flags) -> const assimp::scene&
    {
        const auto* aiScene = ::importer.ReadFile(path.string(), std::to_underlying(flags));

        if (!aiScene                                                                ) throw std::runtime_error{ "Failed to create scene!" };
        if (!aiScene->mFlags & std::to_underlying(assimp::e_scene_flags::incomplete)) throw std::runtime_error{ "Scene is incomplete!"    };
        if (!aiScene->mRootNode                                                     ) throw std::runtime_error{ "Scene has no root node!" };

        return *aiScene;
    }
    auto load_scene       (const std::filesystem::path& path) -> const assimp::scene&
    {
        return read_file(path, 
            assimp::e_processing_flags::calculate_tangent_space  | 
            assimp::e_processing_flags::find_invalid_data        | 
            assimp::e_processing_flags::fix_in_facing_normals    | 
            assimp::e_processing_flags::generate_bounding_boxes  | 
            assimp::e_processing_flags::generate_smooth_normals  | 
            assimp::e_processing_flags::generate_uv_coordinates  | 
            assimp::e_processing_flags::improve_cache_locality   | 
            assimp::e_processing_flags::join_identical_vertices  | 
            assimp::e_processing_flags::optimize_graph           | 
            assimp::e_processing_flags::optimize_meshes          | 
            assimp::e_processing_flags::sort_by_primitive_type   | 
            assimp::e_processing_flags::split_large_meshes       | 
            assimp::e_processing_flags::transform_uv_coordinates | 
            assimp::e_processing_flags::triangulate              );
    }
    auto get_texture      (const assimp::material& material, assimp::e_texture_type type, fox::uint32_t mapping = 0u) -> std::optional<std::string>
    {
        auto name   = assimp::string{};
        auto result = static_cast<assimp::e_result>(material.GetTexture(static_cast<aiTextureType>(type), mapping, &name));

        if   (result == assimp::e_result::success) return std::string{ name.C_Str() };
        else                                       return std::nullopt;
    }
    auto get_texture_count(const assimp::material& material, assimp::e_texture_type type) -> fox::uint32_t
    {
        return material.GetTextureCount(static_cast<aiTextureType>(type));
    }
}
