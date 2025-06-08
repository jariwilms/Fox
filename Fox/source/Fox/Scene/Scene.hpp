#pragma once

#include "Fox/Scene/Actor.hpp"

namespace fox::scn
{
    class Scene
    {
    public:
        Scene() = default;

        Actor& create_actor();
        void   destroy_actor(Actor& actor);

        void set_parent(Actor& parent, Actor& child);
        void unset_parent(Actor& child);

              Actor& find_actor(ecs::id_t id)
        {
            return *m_actors.at(id);
        }
        const Actor& find_actor(ecs::id_t id) const
        {
            return *m_actors.at(id);
        }

    private:
        std::unordered_map<ecs::id_t, std::shared_ptr<scn::Actor>> m_actors{};
    };
}
