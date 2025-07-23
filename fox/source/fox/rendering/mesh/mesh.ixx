export module fox.rendering.mesh;

import std;
import fox.core.types;
import fox.rendering.vertex_array;

export namespace fox::gfx
{
    struct mesh
    {
    public:
        explicit mesh(std::shared_ptr<gfx::vertex_array> vertexArray)
            : vertexArray{ vertexArray } {}

        void bind       () const
        {
            vertexArray->bind();
        }
        auto index_count() const -> fox::count_t
        {
            return vertexArray->index_count();
        }

    private:
        std::shared_ptr<gfx::vertex_array> vertexArray;
    };
}
