#pragma once

#include "Helix/ECS/Registry.hpp"
#include "Helix/ECS/Components/Components.hpp"

namespace hlx
{
    class Scene
    {
    public:
        Scene() = default;

        Entity create_entity();
        void destroy_entity(Entity entity);

        Entity add_child(Entity parent);
        void set_child(Entity parent, Entity child);
        void remove_child(Entity parent, Entity child);

        std::vector<Entity> entities{};
    };

    class Actor : public Entity
    {
    public:
        Actor() = default;

        std::weak_ptr<Actor> parent{};
        std::vector<std::shared_ptr<Actor>> children{};
    };

    class TestScene
    {
    public:
        TestScene() = default;

        std::shared_ptr<Actor> create_actor()
        {

        }

        std::vector<std::shared_ptr<Actor>> actors{};
    };
}
