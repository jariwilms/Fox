#pragma once

#include "Actor.hpp"

namespace fox
{
    class Scene
    {
    public:
        Scene() = default;

        std::shared_ptr<Actor> create_actor();
        void destroy_actor(std::shared_ptr<Actor> actor);

        void set_parent(std::shared_ptr<Actor> parent, std::shared_ptr<Actor> child);
        void unset_parent(std::shared_ptr<Actor> child);

        const std::vector<std::shared_ptr<Actor>>& actors() const
        {
            return m_actors;
        }

    private:
        std::vector<std::shared_ptr<Actor>> m_actors{};
    };
}
