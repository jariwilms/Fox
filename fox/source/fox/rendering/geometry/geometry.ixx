export module fox.rendering.geometry;

import std;

import fox.core.types;
import fox.rendering.mesh;
import fox.rendering.layout;
import fox.rendering.geometry.data;
import fox.io.model_importer;
import fox.rendering.buffer;
import fox.rendering.vertex_array;

export namespace fox::gfx::geometry
{
    std::shared_ptr<gfx::mesh> plane;
    std::shared_ptr<gfx::mesh> cube;
    std::shared_ptr<gfx::mesh> sphere;

    void initialize_plane ()
    {
        auto layout2f = gfx::vertex_layout<gfx::vertex_attribute<fox::float32_t, 2u>>{};
        auto layout3f = gfx::vertex_layout<gfx::vertex_attribute<fox::float32_t, 3u>>{};

              auto vertexArray = gfx::vertex_array                 ::create();
        const auto positions   = gfx::vertex_buffer<fox::float32_t>::create(data::plane::positions  );
        const auto normals     = gfx::vertex_buffer<fox::float32_t>::create(data::plane::normals    );
        const auto tangents    = gfx::vertex_buffer<fox::float32_t>::create(data::plane::tangents   );
        const auto coordinates = gfx::vertex_buffer<fox::float32_t>::create(data::plane::coordinates);
        const auto indices     = gfx::index_buffer                 ::create(data::plane::indices    );

        vertexArray->tie(positions  , layout3f);
        vertexArray->tie(normals    , layout3f);
        vertexArray->tie(tangents   , layout3f);
        vertexArray->tie(coordinates, layout2f);
        vertexArray->tie(indices              );

        plane = std::make_shared<gfx::mesh>(vertexArray);
    }
    void initialize_cube  ()
    {
        auto layout2f = gfx::vertex_layout<gfx::vertex_attribute<fox::float32_t, 2u>>{};
        auto layout3f = gfx::vertex_layout<gfx::vertex_attribute<fox::float32_t, 3u>>{};

        auto vertexArray = gfx::vertex_array::create();
        const auto positions   = gfx::vertex_buffer<fox::float32_t>::create(data::cube::positions  );
        const auto normals     = gfx::vertex_buffer<fox::float32_t>::create(data::cube::normals    );
        const auto tangents    = gfx::vertex_buffer<fox::float32_t>::create(data::cube::tangents   );
        const auto coordinates = gfx::vertex_buffer<fox::float32_t>::create(data::cube::coordinates);
        const auto indices     = gfx::index_buffer                 ::create(data::cube::indices    );

        vertexArray->tie(positions  , layout3f);
        vertexArray->tie(normals    , layout3f);
        vertexArray->tie(tangents   , layout3f);
        vertexArray->tie(coordinates, layout2f);
        vertexArray->tie(indices              );

        cube = std::make_shared<gfx::mesh>(vertexArray);
    }
    void initialize_sphere()
    {
        sphere = io::model_importer::import2("models/sphere/Sphere.gltf")->meshes.at(0u);
    }

    void initialize()
    {
        initialize_plane ();
        initialize_cube  ();
        initialize_sphere();
    }
}
