#pragma once

#include "stdafx.hpp"

#include <entt/entt.hpp>

#include "Helix/ECS/Components/Transform.hpp"

namespace hlx
{
    class Registry
    {
    public:
        static void init()
        {

        }

        static Entity create()
        {
            Entity entity{ s_registry.create() };
            add_component<Transform>(entity);

            return entity;
        }
        static void destroy(const Entity& entity)
        {
            throw std::runtime_error{ "TODO: destroy entity" };
            s_registry.destroy(entity.id());
        }

        template<typename... T>
        static bool has_component(const Entity& entity)
        {
            return s_registry.all_of<T...>(entity.id());
        }
        template<typename T, typename... Args>
        static T& add_component(const Entity& entity, Args&&... args)
        {
            return s_registry.emplace<T>(entity.id(), std::forward<Args>(args)...);
        }
        template<typename T>
        static T& get_component(const Entity& entity)
        {
            return s_registry.get<T>(entity.id());
        }
        template<typename T>
        static void remove_component(const Entity& entity)
        {
            s_registry.remove<T>(entity.id());
        }
        template<> static void remove_component<Transform>(const Entity& entity) = delete;

        //TODO: wrapper for entity group
        template<typename... T>
        static auto view()
        {
            return s_registry.view<T...>();
        }
        template<typename... T>
        static auto group()
        {
            return s_registry.group<T...>();
        }

    private:
        static inline entt::basic_registry<Id> s_registry;
    };
}
