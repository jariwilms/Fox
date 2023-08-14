#include "stdafx.hpp"

#include "Scene.hpp"

namespace hlx
{
    Entity Scene::create_entity()
    {
        return entities.emplace_back(Registry::create());
    }
    void Scene::destroy_entity(Entity entity)
    {
        const auto it = std::find(entities.begin(), entities.end(), entity);
        if (it == entities.end()) return;

        auto& relationship = Registry::get_component<RelationshipComponent>(entity);
        for (const auto& child : relationship.children) destroy_entity(child); //TODO: BFS instead of recursion

        entities.erase(it);
        Registry::destroy(entity);
    }

    Entity Scene::add_child(Entity parent)
    {
        auto childEntity = create_entity();
        set_child(parent, childEntity);

        return childEntity;
    }
    void Scene::set_child(Entity parent, Entity child)
    {
        auto it = std::find(entities.begin(), entities.end(), child);
        if (it != entities.end()) entities.erase(it);

        auto& parentRelationship = Registry::get_component<RelationshipComponent>(parent);
        it = std::find(parentRelationship.children.begin(), parentRelationship.children.end(), child);
        if (it == entities.end()) parentRelationship.children.emplace_back(child);

        auto& childRelationship = Registry::get_component<RelationshipComponent>(child);
        childRelationship.parent = parent;
    }
    void Scene::remove_child(Entity parent, Entity child)
    {

    }
}
