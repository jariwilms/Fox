export module vendor.assimp:types;

import std;
import <assimp/importer.hpp>;
import <assimp/postprocess.h>;
import <assimp/scene.h>;
import fox.core.types;

export namespace assimp
{
    enum class texture_type_e : std::underlying_type_t<aiTextureType>
    {
        albedo             = aiTextureType_DIFFUSE  , 
        normal             = aiTextureType_NORMALS  , 
        metallic_roughness = aiTextureType_METALNESS, 
    };
    enum class processing_flags_e : std::underlying_type_t<aiPostProcessSteps>
    {
        calculate_tangent_space  = aiProcess_CalcTangentSpace     , //Calculate tangents and bitangents
        find_invalid_data        = aiProcess_FindInvalidData      , //Removes/fixes invalid mesh data
        fix_in_facing_normals    = aiProcess_FixInfacingNormals   , //Inverts inwards facing normals
        generate_bounding_boxes  = aiProcess_GenBoundingBoxes     , //Generates AABB's for each mesh
        generate_smooth_normals  = aiProcess_GenSmoothNormals     , //Generate normals for all faces of all meshes
        generate_uv_coordinates  = aiProcess_GenUVCoords          , //Converts non UV-mappings to texture coordinates channels
        improve_cache_locality   = aiProcess_ImproveCacheLocality , //Reorder triangles for better vertex cache locality
        join_identical_vertices  = aiProcess_JoinIdenticalVertices, //Let each mesh contain unique vertices
        optimize_graph           = aiProcess_OptimizeGraph        , //Nodes without animations, bones etc. are collapsed and joined
        optimize_meshes          = aiProcess_OptimizeMeshes       , //Reduces the number of meshes
        sort_by_primitive_type   = aiProcess_SortByPType          , //Split meshes with >1 primitive type into submeshes
        split_large_meshes       = aiProcess_SplitLargeMeshes     , //Split up larges meshes into smaller meshes
        transform_uv_coordinates = aiProcess_TransformUVCoords    , //Applies per-texture UV transformations
        triangulate              = aiProcess_Triangulate          , //Split up faces with >3 indices into triangles
    };
    enum class scene_flags_e
    {
        allow_shared       = AI_SCENE_FLAGS_ALLOW_SHARED      , 
        incomplete         = AI_SCENE_FLAGS_INCOMPLETE        , 
        non_verbose_format = AI_SCENE_FLAGS_NON_VERBOSE_FORMAT, 
        terrain            = AI_SCENE_FLAGS_TERRAIN           , 
        validated          = AI_SCENE_FLAGS_VALIDATED         , 
        validation_warning = AI_SCENE_FLAGS_VALIDATION_WARNING, 
    };
    enum class result_e
    {
        failure = AI_FAILURE, 
        success = AI_SUCCESS, 
    };

    using face         = ::aiFace;
    using importer     = ::Assimp::Importer;
    using material     = ::aiMaterial;
    using mesh         = ::aiMesh;
    using node         = ::aiNode;
    using scene        = ::aiScene;
    using string       = ::aiString;
    using vector_2d    = ::aiVector2D;
    using vector_3d    = ::aiVector3D;

    constexpr auto operator|(assimp::processing_flags_e first, assimp::processing_flags_e second) { return static_cast<assimp::processing_flags_e>(std::to_underlying(first) | std::to_underlying(second)); };
    constexpr auto operator&(assimp::scene_flags_e      first, assimp::scene_flags_e      second) { return static_cast<assimp::scene_flags_e     >(std::to_underlying(first) & std::to_underlying(second)); };
}
