#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
    class Material
    {
    public:
        Material() = default;

        std::string_view name() const
        {
            return m_name;
        }
        const glm::uvec4& color() const
        {
            return m_color;
        }
        float metallic() const
        {
            return m_metallic;
        }
        float roughness() const
        {
            return m_roughness;
        }
        const std::shared_ptr<Texture2D> albedo() const
        {
            return m_albedo;
        }
        const std::shared_ptr<Texture2D> normal() const
        {
            return m_normal;
        }

        bool operator==(const Material& other)
        {
            return
                m_color    == other.m_color    &&
                m_metallic == other.m_metallic &&
                m_roughness == other.m_roughness &&
                m_albedo   == other.m_albedo   &&
                m_normal   == other.m_normal    ;
        }

    private:
        std::string m_name{ "Default" };

        glm::uvec4 m_color{ 1.0f, 1.0f, 1.0f, 1.0f };
        float m_metallic{ 0.0f };
        float m_roughness{ 0.0f };

        std::shared_ptr<Texture2D> m_albedo{};
        std::shared_ptr<Texture2D> m_normal{};
    };
}
