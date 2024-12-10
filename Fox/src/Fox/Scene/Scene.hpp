#pragma once

#include "Actor.hpp"

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

              Actor& find_actor(fox::id_t id)
        {
            return *m_actors.at(static_cast<fox::uint32_t>(id));
        }
        const Actor& find_actor(fox::id_t id) const
        {
            return *m_actors.at(static_cast<fox::uint32_t>(id));
        }

    private:
        std::unordered_map<fox::uint32_t, std::shared_ptr<scn::Actor>> m_actors{};
    };
}
