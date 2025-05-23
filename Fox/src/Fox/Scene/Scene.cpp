#include "stdafx.hpp"

#include "Scene.hpp"

namespace fox::scn
{
    Actor& Scene::create_actor()
    {
        auto actor = std::make_shared<scn::Actor>();
        const auto& it = m_actors.emplace(std::make_pair(actor->id(), std::move(actor)));
        
        return *it.first->second;
    }
    void   Scene::destroy_actor(Actor& actor)
    {
        unset_parent(actor);

        auto& rls = actor.get_component<cmp::RelationshipComponent>().get();
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

        auto& rel  = child.get_component<cmp::RelationshipComponent>().get();
        auto& prel = parent.get_component<cmp::RelationshipComponent>().get();

        prel.children.emplace_back(child.id());
        rel.parent = parent.id();
    }
    void Scene::unset_parent(Actor& child)
    {
        auto& rel = child.get_component<cmp::RelationshipComponent>().get();

        if (rel.parent)
        {
            const auto& parent = rel.parent.value();
                  auto& prel    = reg::get_component<cmp::RelationshipComponent>(parent).get();

            const auto& it = std::find(prel.children.begin(), prel.children.end(), child.id());
            if (it != prel.children.end())
            {
                prel.children.erase(it);
            }

            rel.parent = std::nullopt;
        }
    }
}
