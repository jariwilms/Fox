#pragma once

#include <memory>

#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/matrix.hpp>

#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/buffer/vertexarray.hpp>
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

        static std::shared_ptr<gfx::Model> import(const std::filesystem::path& path);

    private:
        static void create_nodes(gfx::Model& model, fox::uint32_t nodeIndex, const aiScene& aiScene, const aiNode& aiNode);

        static inline std::shared_ptr<gfx::Texture2D> s_defaultAlbedoTexture{};
        static inline std::shared_ptr<gfx::Texture2D> s_defaultNormalTexture{};
        static inline std::shared_ptr<gfx::Texture2D> s_defaultARMTexture   {};
    };
}
