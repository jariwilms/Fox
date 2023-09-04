#include "stdafx.hpp"

#include "Scene.hpp"

namespace hlx
{
    std::shared_ptr<hlx::Actor> Scene::create_actor()
    {
        return actors.emplace_back(std::make_shared<Actor>());
    }
    void Scene::destroy_actor(std::shared_ptr<Actor> actor)
    {
        auto it = std::find(actors.begin(), actors.end(), actor);
        if (it != actors.end()) actors.erase(it);
    }

    void Scene::set_parent(std::shared_ptr<Actor> parent, std::shared_ptr<Actor> child)
    {
        if (!parent || !child) return;

        unset_parent(child);
        parent->children.emplace_back(child);
        child->parent = parent;

        auto& parentTransform = parent->get_component<TransformComponent>();
        Transform& t = parentTransform;
        auto& childTransform = child->get_component<TransformComponent>();

        childTransform.parent = &t;
    }
    void Scene::unset_parent(std::shared_ptr<Actor> child)
    {
        auto& parent = child->parent;
        if (!parent.expired())
        {
            auto parentPtr = parent.lock();
            auto& children = parentPtr->children;
            auto it = std::find(children.begin(), children.end(), child);
            if (it != children.end()) children.erase(it);

            actors.emplace_back(child);

            auto& transform = child->get_component<TransformComponent>();
            auto& parentTransform = Registry::get_component<TransformComponent>(parentPtr->id());
            
            
            //transform.parent = std::shared_ptr<TransformComponent>(&parentTransform);
            transform.parent = &parentTransform;
        }
    }
}
