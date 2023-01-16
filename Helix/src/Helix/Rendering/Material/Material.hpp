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

        bool operator==(const Material& other)
        {
            return
                m_color    == other.m_color    &&
                m_metallic == other.m_metallic &&
                m_rougness == other.m_rougness &&
                m_albedo   == other.m_albedo   &&
                m_normal   == other.m_normal    ;
        }

    private:
        std::string m_name{};

        glm::uvec4 m_color{};
        float m_metallic{};
        float m_rougness{};

        std::shared_ptr<Texture2D> m_albedo{};
        std::shared_ptr<Texture2D> m_normal{};
    };
}
