export module fox.rendering.model;

import std;

import fox.core.types;
import fox.core.transform;
import fox.rendering.material;
import fox.rendering.mesh;

export namespace fox::gfx
{
    class Model
    {
    public:
        struct Node
        {
            Node() = default;

            fox::Transform               transform;
            std::optional<fox::uint32_t> mesh;
            std::optional<fox::uint32_t> material;
            std::vector  <fox::size_t  > children;
        };

        Model()
            : nodes{ Node{} }, meshes{}, materials{} {}

        std::vector<Node>                           nodes;
        std::vector<std::shared_ptr<gfx::Mesh    >> meshes;
        std::vector<std::shared_ptr<gfx::Material>> materials;
    };
}
