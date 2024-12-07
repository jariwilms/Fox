#pragma once

#include "stdafx.hpp"

#include <entt/entt.hpp>

#include "Fox/ECS/Components/Component.hpp"

namespace fox
{
    namespace reg::api
    {
        inline entt::basic_registry<fox::id_t> registry{};
    }
    namespace reg
    {
        static fox::id_t create()
        {
            return api::registry.create();
        }
        static void      destroy(fox::id_t id)
        {
            api::registry.destroy(id);
        }

        template<typename... T>
        static bool has_component(fox::id_t id)
        {
            static_assert(std::is_base_of_v<ecs::Component, T>);

            return api::registry.all_of<T...>(id);
        }
        template<typename T, typename... Args>
        static T&   add_component(fox::id_t id, Args&&... args)
        {
            return api::registry.emplace<T>(id, std::forward<Args>(args)...);
        }
        template<typename T>
        static T&   get_component(fox::id_t id)
        {
            return api::registry.get<T>(id);
        }
        template<typename T>
        static void remove_component(fox::id_t id)
        {
            api::registry.remove<T>(id);
        }

        template<typename... T>
        static auto view() //TODO: wrapper for entity group (using my_view = entt::basic_view ofzoiets)
        {
            return api::registry.view<T...>();
        }
        template<typename... T>
        static auto group()
        {
            return api::registry.group<T...>();
        }
    };
}
