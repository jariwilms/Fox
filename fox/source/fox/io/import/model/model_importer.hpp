#pragma once

#include <stdafx.hpp>

#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/buffer/vertex_array.hpp>
#include <fox/rendering/model/model.hpp>
#include <fox/rendering/texture/texture.hpp>

namespace fox::io
{
    class ModelImporter
    {
    public:
        enum class TextureType
        {
            Albedo, 
            Normal, 
            MetallicRoughness, 
        };

        static void init();

        static auto import(const std::filesystem::path& path) -> std::shared_ptr<gfx::Model>;

    private:
        static auto load_scene        (const std::filesystem::path& path) -> const aiScene&;
        static auto get_assimp_texture(const std::filesystem::path& path, const aiMaterial& aiMaterial, TextureType type) -> std::optional<std::shared_ptr<gfx::Texture2D>>;
        static void create_nodes      (std::shared_ptr<gfx::Model> model, fox::size_t nodeIndex, const aiScene& aiScene, const aiNode& aiRootNode);

        static inline Assimp::Importer                importer_;
        static inline std::shared_ptr<gfx::Texture2D> defaultAlbedoTexture_;
        static inline std::shared_ptr<gfx::Texture2D> defaultNormalTexture_;
        static inline std::shared_ptr<gfx::Texture2D> defaultARMTexture_;
    };
}
