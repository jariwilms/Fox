#pragma once

#include <memory>
#include <unordered_map>

#include <fox/scene/actor.hpp>

namespace fox::scene
{
    class Scene
    {
    public:
        Scene() = default;

        auto create_actor () -> scene::Actor&;
        void destroy_actor(scene::Actor& actor);

        void set_parent  (scene::Actor& parent, scene::Actor& child);
        void unset_parent(scene::Actor& child);

        auto find_actor(fox::id_t id) -> scene::Actor&
        {
            return *m_actors.at(id);
        }
        auto find_actor(fox::id_t id) const -> const scene::Actor&
        {
            return *m_actors.at(id);
        }

    private:
        std::unordered_map<fox::id_t, std::shared_ptr<scene::Actor>> m_actors{};
    };
}
