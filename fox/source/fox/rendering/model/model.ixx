export module fox.rendering.model;

import std;
import fox.core.types;
import fox.core.transform;
import fox.rendering.material;
import fox.rendering.mesh;

export namespace fox::gfx
{
    class model
    {
    public:
        struct node
        {
            node() = default;

            fox::transform               transform;
            std::optional<fox::uint32_t> mesh;
            std::optional<fox::uint32_t> material;
            std::vector  <fox::size_t  > children;
        };

        model()
            : nodes{ node{} }, meshes{}, materials{} {}

        std::vector<node>                           nodes;
        std::vector<std::shared_ptr<gfx::mesh    >> meshes;
        std::vector<std::shared_ptr<gfx::material>> materials;
    };
}
