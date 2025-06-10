#include "stdafx.hpp"

#include "Scene.hpp"

namespace fox::scene
{
    auto Scene::create_actor() -> Actor&
    {
        auto        actor = std::make_shared<scene::Actor>();
        auto const& it    = m_actors.emplace(std::make_pair(actor->id(), std::move(actor)));
        
        return *it.first->second;
    }
    void Scene::destroy_actor(Actor& actor)
    {
        unset_parent(actor);

        auto& rls = actor.get_component<ecs::RelationshipComponent>().get();
        for (auto& id : rls.children)
        {
            auto& childActor = m_actors.at(id);
            destroy_actor(*childActor);
        }

        m_actors.erase(actor.id());
    }

    void Scene::set_parent(Actor& parent, Actor& child)
    {
        unset_parent(child);

        auto& rel  = child.get_component<ecs::RelationshipComponent>().get();
        auto& prel = parent.get_component<ecs::RelationshipComponent>().get();

        prel.children.emplace_back(child.id());
        rel.parent = parent.id();
    }
    void Scene::unset_parent(Actor& child)
    {
        auto& rel = child.get_component<ecs::RelationshipComponent>().get();

        if (rel.parent)
        {
            const auto& parent   = *rel.parent;
                  auto& relative = reg::get_component<ecs::RelationshipComponent>(parent).get();

            const auto& it = std::find(relative.children.begin(), relative.children.end(), child.id());
            if (it != relative.children.end())
            {
                relative.children.erase(it);
            }

            rel.parent = std::nullopt;
        }
    }
}
