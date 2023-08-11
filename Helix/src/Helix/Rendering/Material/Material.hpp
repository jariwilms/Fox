#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"

namespace hlx
{
    //class Material
    //{
    //public:
    //    Material() = default;

    //    std::string name{ "Default" };

    //    Vector4u color{ 1.0f, 1.0f, 1.0f, 1.0f };
    //    std::shared_ptr<Texture2D> albedo{};
    //    std::shared_ptr<Texture2D> normal{};
    //    float metallic{ 0.0f };
    //    float roughness{ 0.0f };

    //    bool operator==(const Material& other)
    //    {
    //        return
    //            color     == other.color     &&
    //            metallic  == other.metallic  &&
    //            roughness == other.roughness &&
    //            albedo    == other.albedo    &&
    //            normal    == other.normal     ;
    //    }
    //};

    struct Material
    {
    public:
        Material(const std::string& name, std::shared_ptr<const Pipeline> pipeline)
            : name{ name }, pipeline{ pipeline } {}

        std::string name{};
        std::shared_ptr<const Pipeline> pipeline{};
    };
    class DefaultMaterial : public Material
    {
    public:
        DefaultMaterial(const std::string& name, std::shared_ptr<const Pipeline> pipeline)
            : Material{ name, pipeline } {}

        Vector4u color{ 1.0f, 1.0f, 1.0f, 1.0f }; //Required to be vec4 because of GPU alignment
        std::shared_ptr<Texture2D> albedo{};
        std::shared_ptr<Texture2D> normal{};
        float metallic{ 0.0f };
        float roughness{ 0.0f };
    };
}
