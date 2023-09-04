#pragma once

#include "Actor.hpp"

namespace hlx
{
    class Scene
    {
    public:
        Scene() = default;

        std::shared_ptr<Actor> create_actor();
        void destroy_actor(std::shared_ptr<Actor> actor);
        //std::shared_ptr<Actor> duplicate_actor(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> parent = {});

        void set_parent(std::shared_ptr<Actor> parent, std::shared_ptr<Actor> child);
        void unset_parent(std::shared_ptr<Actor> child);

        std::vector<std::shared_ptr<Actor>> actors{};
    };
}
