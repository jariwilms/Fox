module;

#include <fox/rendering/buffer/Buffer.hpp>

export module fox.rendering.geometry;

import std;

import fox.core.types;
import fox.rendering.mesh;
import fox.rendering.layout;
import fox.rendering.geometry.data;
import fox.io.model_importer;
import fox.rendering.vertex_array;

export namespace fox::gfx::geometry
{
    std::shared_ptr<gfx::Mesh> plane;
    std::shared_ptr<gfx::Mesh> cube;
    std::shared_ptr<gfx::Mesh> sphere;

    void plane_init()
    {
        auto layout2f = gfx::layout_t<gfx::attribute_t<fox::float32_t, 2u>>{};
        auto layout3f = gfx::layout_t<gfx::attribute_t<fox::float32_t, 3u>>{};

              auto vertexArray = gfx::VertexArray                 ::create();
        const auto positions   = gfx::VertexBuffer<fox::float32_t>::create(data::plane::positions  );
        const auto normals     = gfx::VertexBuffer<fox::float32_t>::create(data::plane::normals    );
        const auto tangents    = gfx::VertexBuffer<fox::float32_t>::create(data::plane::tangents   );
        const auto coordinates = gfx::VertexBuffer<fox::float32_t>::create(data::plane::coordinates);
        const auto indices     = gfx::IndexBuffer                 ::create(data::plane::indices    );

        vertexArray->tie(positions  , layout3f);
        vertexArray->tie(normals    , layout3f);
        vertexArray->tie(tangents   , layout3f);
        vertexArray->tie(coordinates, layout2f);
        vertexArray->tie(indices              );

        plane = std::make_shared<gfx::Mesh>(vertexArray);
    }
    void cube_init()
    {
        auto layout2f = gfx::layout_t<gfx::attribute_t<fox::float32_t, 2u>>{};
        auto layout3f = gfx::layout_t<gfx::attribute_t<fox::float32_t, 3u>>{};

        auto vertexArray = gfx::VertexArray::create();
        const auto positions   = gfx::VertexBuffer<fox::float32_t>::create(data::cube::positions  );
        const auto normals     = gfx::VertexBuffer<fox::float32_t>::create(data::cube::normals    );
        const auto tangents    = gfx::VertexBuffer<fox::float32_t>::create(data::cube::tangents   );
        const auto coordinates = gfx::VertexBuffer<fox::float32_t>::create(data::cube::coordinates);
        const auto indices     = gfx::IndexBuffer                 ::create(data::cube::indices    );

        vertexArray->tie(positions  , layout3f);
        vertexArray->tie(normals    , layout3f);
        vertexArray->tie(tangents   , layout3f);
        vertexArray->tie(coordinates, layout2f);
        vertexArray->tie(indices              );

        cube = std::make_shared<gfx::Mesh>(vertexArray);
    }
    void sphere_init()
    {
        sphere = io::ModelImporter::import2("models/sphere/Sphere.gltf")->meshes.at(0u);
    }

    void init()
    {
        plane_init();
        cube_init();
        sphere_init();
    }
}
