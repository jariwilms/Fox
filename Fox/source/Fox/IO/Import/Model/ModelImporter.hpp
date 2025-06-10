#pragma once

#include "stdafx.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"
#include "Fox/Rendering/Buffer/VertexArray.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

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
        static void create_nodes(gfx::Model& model, fox::uint32_t nodeIndex, const aiScene& asiScene, const aiNode& asiNode);

        static inline auto s_defaultAlbedoTexture = std::shared_ptr<gfx::Texture2D>{};
        static inline auto s_defaultNormalTexture = std::shared_ptr<gfx::Texture2D>{};
        static inline auto s_defaultARMTexture    = std::shared_ptr<gfx::Texture2D>{};
    };
}
