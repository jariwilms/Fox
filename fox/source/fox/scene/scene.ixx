export module fox.scene;

import std;
import <entt/entt.hpp>;
import fox.ecs.registry;
import fox.core.types;
import fox.scene.actor;
import fox.ecs.components;

export namespace fox::scene
{
    class Scene
    {
    public:
        Scene() = default;

        auto create_actor() -> scene::Actor&
        {
                  auto  actor = std::make_shared<scene::Actor>();
            const auto& it    = actors_.emplace(std::make_pair(actor->id(), std::move(actor)));

            return *it.first->second;
        }
        void destroy_actor(Actor& actor)
        {
            unset_parent(actor);

            auto& rls = actor.get_component<ecs::RelationshipComponent>().value();
            for (auto& id : rls.children)
            {
                auto& childActor = actors_.at(id);
                destroy_actor(*childActor);
            }

            actors_.erase(actor.id());
        }

        void set_parent(Actor& parent, Actor& child)
        {
            unset_parent(child);

            auto& rel  = child.get_component<ecs::RelationshipComponent>().value();
            auto& prel = parent.get_component<ecs::RelationshipComponent>().value();

            prel.children.emplace_back(child.id());
            rel.parent = parent.id();
        }
        void unset_parent(Actor& child)
        {
            auto& rel = child.get_component<ecs::RelationshipComponent>().value();

            if (rel.parent)
            {
                const auto& parent   = *rel.parent;
                auto& relative = registry::get_component<ecs::RelationshipComponent>(parent).value();

                const auto& it = std::find(relative.children.begin(), relative.children.end(), child.id());
                if (it != relative.children.end())
                {
                    relative.children.erase(it);
                }

                rel.parent = std::nullopt;
            }
        }

        auto find_actor(fox::id_t id) -> scene::Actor&
        {
            return *actors_.at(id);
        }
        auto find_actor(fox::id_t id) const -> const scene::Actor&
        {
            return *actors_.at(id);
        }

    private:
        std::unordered_map<fox::id_t, std::shared_ptr<scene::Actor>> actors_{};
    };
}
