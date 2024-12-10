#include "stdafx.hpp"

#include "Scene.hpp"

namespace fox::scn
{
    Actor& Scene::create_actor()
    {
        auto actor = std::make_shared<scn::Actor>();
        const auto& it = m_actors.emplace(std::make_pair(static_cast<fox::uint32_t>(actor->id()), std::move(actor)));
        
        return *it.first->second;
    }
    void   Scene::destroy_actor(Actor& actor)
    {
        unset_parent(actor);

        auto& rc = actor.get_component<ecs::RelationshipComponent>();
        for (auto& id : rc.children)
        {
            auto& childActor = m_actors.at(static_cast<fox::uint32_t>(id));
            destroy_actor(*childActor);
        }

        m_actors.erase(static_cast<fox::uint32_t>(actor.id()));
    }

    void Scene::set_parent(Actor& parent, Actor& child)
    {
        unset_parent(child);

        auto& rc  = child.get_component<ecs::RelationshipComponent>();
        auto& prc = parent.get_component<ecs::RelationshipComponent>();

        prc.children.emplace_back(child.id());
        rc.parent = parent.id();
    }
    void Scene::unset_parent(Actor& child)
    {
        auto& rc = child.get_component<ecs::RelationshipComponent>();

        if (rc.parent)
        {
            const auto& parent = rc.parent.value();
                  auto& prc    = reg::get_component<ecs::RelationshipComponent>(parent);

            const auto& it = std::find(prc.children.begin(), prc.children.end(), child.id());
            if (it != prc.children.end())
            {
                prc.children.erase(it);
            }

            rc.parent = std::nullopt;
        }
    }
}
