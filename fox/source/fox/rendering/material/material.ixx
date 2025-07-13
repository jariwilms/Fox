module;

#include <fox/rendering/shader/shader.hpp>
#include <fox/rendering/texture/texture.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>

export module fox.rendering.material;

import std;

export namespace fox::gfx
{
    struct Material
    {
        std::string                           name           { "Material"  };
        fox::Vector4f                         color          { vector::one };
        fox::float32_t                        roughnessFactor{ 0.5f };
        fox::float32_t                        metallicFactor { 0.0f };

        std::shared_ptr<const gfx::Texture2D> albedo;
        std::shared_ptr<const gfx::Texture2D> normal;
        std::shared_ptr<const gfx::Texture2D> arm;
        std::shared_ptr<const gfx::Texture2D> emissive;

        std::shared_ptr<const gfx::Shader>    shader;
    };
}
