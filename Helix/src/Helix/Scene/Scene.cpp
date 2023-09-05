#include "stdafx.hpp"

#include "Scene.hpp"

namespace hlx
{
    std::shared_ptr<hlx::Actor> Scene::create_actor()
    {
        return m_actors.emplace_back(std::make_shared<Actor>());
    }
    void Scene::destroy_actor(std::shared_ptr<Actor> actor)
    {
        auto it = std::find(m_actors.begin(), m_actors.end(), actor);
        if (it != m_actors.end())
        {
            unset_parent(actor);

            auto& rc = actor->get_component<RelationshipComponent>();
            for (auto& id : rc.children)
            {
                auto it = std::find_if(m_actors.begin(), m_actors.end(), [&](std::shared_ptr<Actor> actor) { return actor->id() == id; });
                if (it != m_actors.end()) destroy_actor(*it);
            }

            m_actors.erase(it);
        }
    }

    void Scene::set_parent(std::shared_ptr<Actor> parent, std::shared_ptr<Actor> child)
    {
        if (!parent || !child) return;

        unset_parent(child);

        auto& rc = child->get_component<RelationshipComponent>();
        auto& prc = parent->get_component<RelationshipComponent>();

        prc.children.emplace_back(child->id());
        rc.parent = parent->id();
    }
    void Scene::unset_parent(std::shared_ptr<Actor> child)
    {
        if (!child) return;

        auto& rc = child->get_component<RelationshipComponent>();
        if (rc.parent.has_value())
        {
            const auto& parent = rc.parent.value();
            auto& prc = Registry::get_component<RelationshipComponent>(parent);

            if (auto it = std::find(prc.children.begin(), prc.children.end(), child->id()); it != prc.children.end())
            {
                prc.children.erase(it);
            }

            rc.parent = std::nullopt;
        }
    }
}
