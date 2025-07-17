module;

#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

export module vendor.assimp:types;

import std;
import fox.core.types;

export namespace assimp
{
    enum class texture_type : std::underlying_type_t<aiTextureType>
    {
        albedo             = aiTextureType_DIFFUSE  , 
        normal             = aiTextureType_NORMALS  , 
        metallic_roughness = aiTextureType_METALNESS, 
    };
    enum class processing_flags : fox::uint32_t
    {
        calculate_tangent_space , //Calculate tangents and bitangents
        find_invalid_data       , //Removes/fixes invalid mesh data
        fix_in_facing_normals   , //Inverts inwards facing normals
        generate_bounding_boxes , //Generates AABB's for each mesh
        generate_smooth_normals , //Generate normals for all faces of all meshes
        generate_uv_coordinates , //Converts non UV-mappings to texture coordinates channels
        improve_cache_locality  , //Reorder triangles for better vertex cache locality
        join_identical_vertices , //Let each mesh contain unique vertices
        optimize_graph          , //Nodes without animations, bones etc. are collapsed and joined
        optimize_meshes         , //Reduces the number of meshes
        sort_by_primitive_type  , //Split meshes with >1 primitive type into submeshes
        split_large_meshes      , //Split up larges meshes into smaller meshes
        transform_uv_coordinates, //Applies per-texture UV transformations
        triangulate             , //Split up faces with >3 indices into triangles
    };
    enum class scene_flags
    {
        allow_shared       = AI_SCENE_FLAGS_ALLOW_SHARED      , 
        incomplete         = AI_SCENE_FLAGS_INCOMPLETE        , 
        non_verbose_format = AI_SCENE_FLAGS_NON_VERBOSE_FORMAT, 
        terrain            = AI_SCENE_FLAGS_TERRAIN           , 
        validated          = AI_SCENE_FLAGS_VALIDATED         , 
        validation_warning = AI_SCENE_FLAGS_VALIDATION_WARNING, 
    };
    enum class result
    {
        failure = AI_FAILURE, 
        success = AI_SUCCESS, 
    };

    using node         = ::aiNode;
    using face         = ::aiFace;
    using mesh         = ::aiMesh;
    using vector_2d    = ::aiVector2D;
    using vector_3d    = ::aiVector3D;
    using string       = ::aiString;
    using material     = ::aiMaterial;
    using importer     = ::Assimp::Importer;

    struct scene
    {
        scene(const aiScene* const aiScene)
            : flags{ static_cast<assimp::scene_flags>(aiScene->mFlags) }
            , root { *aiScene->mRootNode } {}

        const assimp::scene_flags flags;
        const assimp::node&       root ;
    };

    constexpr auto operator|(assimp::processing_flags first, assimp::processing_flags second) { return static_cast<assimp::processing_flags>(std::to_underlying(first) | std::to_underlying(second)); };
    constexpr auto operator&(assimp::scene_flags      first, assimp::scene_flags      second) { return static_cast<assimp::scene_flags     >(std::to_underlying(first) & std::to_underlying(second)); };
}
