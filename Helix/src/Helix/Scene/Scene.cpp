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
        auto index{ 0u };
        for (const auto& e : entities)
        {
            if (e == entity) entities.erase(entities.begin() + index);
            ++index;
        }
    }
}
