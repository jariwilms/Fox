#pragma once

#include "stdafx.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Fox/Rendering/Model/Model.hpp"

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

        static std::shared_ptr<gfx::Model> import2(const std::filesystem::path& path);

    private:
        using texptr_t = std::shared_ptr<gfx::Texture2D>;

        static void                    create_nodes(gfx::Model& model, fox::uint32_t nodeIndex, const aiScene& asiScene, const aiNode& asiNode);
        static texptr_t                load_texture(const std::filesystem::path& path);
        static auto                    to_assimp_type(TextureType type);
        static std::optional<texptr_t> get_assimp_texture(const aiMaterial* aiMaterial, TextureType type, const std::filesystem::path& path);

        static inline std::shared_ptr<gfx::Texture2D> s_defaultAlbedoTexture{};
        static inline std::shared_ptr<gfx::Texture2D> s_defaultNormalTexture{};
        static inline std::shared_ptr<gfx::Texture2D> s_defaultARMTexture{};
    };
}
