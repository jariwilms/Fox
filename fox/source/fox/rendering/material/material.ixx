export module fox.rendering.material;

import std;
import fox.core.types.fundamental;
import fox.core.types.math;
import fox.rendering.texture;
import fox.rendering.shader;

export namespace fox::gfx
{
    struct material
    {
        std::string                           name           { "Material"  };
        fox::vector4f                         color          { fox::vector<>::one };
        fox::float32_t                        roughnessFactor{ 0.5f };
        fox::float32_t                        metallicFactor { 0.0f };

        std::shared_ptr<gfx::texture2d> albedo;
        std::shared_ptr<gfx::texture2d> normal;
        std::shared_ptr<gfx::texture2d> arm;
        std::shared_ptr<gfx::texture2d> emissive;

        std::shared_ptr<gfx::shader>    shader;
    };
}
