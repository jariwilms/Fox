export module fox;
export import fox.api;
export import fox.config;
export import fox.core;
export import fox.ecs;
export import fox.input;
export import fox.io;
export import fox.io.model_importer; //remove
export import fox.math;
export import fox.physics;
export import fox.random;
export import fox.rendering;
export import fox.rendering.renderer; //remove?
export import fox.scene;
export import fox.window;

import std;

export namespace fox
{
    struct configuration_e
    {
        std::string   window_title;
        fox::vector2u window_dimensions;
    };

    void initialize()
    {
        api::initialize();

        gfx::geometry     ::init();
        io::model_importer::init();
        gfx::renderer     ::init();
    }
}
