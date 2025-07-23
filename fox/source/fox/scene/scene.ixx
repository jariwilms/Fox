export module fox.scene;
export import fox.scene.actor;

import std;
import fox.core.types;
import fox.ecs.components;
import fox.ecs.registry;

export namespace fox
{
    class scene
    {
    public:
        auto create_actor () -> fox::actor&
        {
            auto actor = std::make_shared<fox::actor>();
            return *actors_.emplace(std::make_pair(actor->id(), std::move(actor))).first->second;
        }
        void destroy_actor(fox::actor& actor)
        {
            unset_parent(actor);

            auto& rls = actor.get_component<ecs::relationship_component>().value();
            for (auto& id : rls.children)
            {
                auto& childactor = actors_.at(id);
                destroy_actor(*childactor);
            }

            actors_.erase(actor.id());
        }

        void set_parent   (fox::actor& parent, fox::actor& child)
        {
            unset_parent(child);

            auto& prel = parent.get_component<ecs::relationship_component>().value();
            auto&  rel = child .get_component<ecs::relationship_component>().value();

            prel.children.emplace_back(child.id());
            rel .parent = parent.id();
        }
        void unset_parent (fox::actor& child)
        {
            auto& rel = child.get_component<ecs::relationship_component>().value();

            if (rel.parent)
            {
                const auto& parent   = *rel.parent;
                      auto& relative = ecs::registry::get_component<ecs::relationship_component>(parent).value();
                const auto& it       = std::find(relative.children.begin(), relative.children.end(), child.id());

                if (it != relative.children.end()) relative.children.erase(it);
                
                rel.parent = std::nullopt;
            }
        }

        auto find_actor   (this auto&& self, fox::id_t id) -> auto&&
        {
            return *self.actors_.at(id);
        }

    private:
        std::unordered_map<fox::id_t, std::shared_ptr<fox::actor>> actors_;
    };
}
