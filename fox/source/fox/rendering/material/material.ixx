module;

#include <fox/rendering/shader/shader.hpp>

export module fox.rendering.material;

import std;

import fox.core.types.fundamental;
import fox.core.types.math;
import fox.rendering.texture;

export namespace fox::gfx
{
    struct Material
    {
        std::string                           name           { "Material"  };
        fox::Vector4f                         color          { vector::one };
        fox::float32_t                        roughnessFactor{ 0.5f };
        fox::float32_t                        metallicFactor { 0.0f };

        std::shared_ptr<gfx::Texture2D> albedo;
        std::shared_ptr<gfx::Texture2D> normal;
        std::shared_ptr<gfx::Texture2D> arm;
        std::shared_ptr<gfx::Texture2D> emissive;

        std::shared_ptr<gfx::Shader>    shader;
    };
}
