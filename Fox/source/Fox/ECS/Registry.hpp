#pragma once

#include <entt/entt.hpp>

import std;

import fox.core.types.fundamental;
import fox.core.types.ecs;
import fox.ecs.component;

namespace fox
{
    namespace registry::api
    {
        using registry_t = entt::basic_registry<fox::id_t>;

        inline registry_t registry{};
    }
    namespace registry
    {
        inline auto create() -> fox::id_t
        {
            return api::registry.create();
        }
        inline void destroy(fox::id_t id)
        {
            api::registry.destroy(id);
        }

        template<typename... T>
        inline auto has_component   (fox::id_t id) -> fox::bool_t
        {
            return api::registry.all_of<T...>(id);
        }
        template<typename T, typename... Args>
        inline auto add_component   (fox::id_t id, Args&&... args) -> T&
        {
            return api::registry.emplace<T>(id, std::forward<Args>(args)...);
        }
        template<typename T>
        inline auto get_component   (fox::id_t id) -> T&
        {
            return api::registry.get<T>(id);
        }
        template<typename T>
        inline void remove_component(fox::id_t id)
        {
            api::registry.remove<T>(id);
        }

        template<typename... T>
        inline auto view() -> auto
        {
            return api::registry.view<T...>();
        }
        template<typename... T>
        inline auto group() -> auto
        {
            return api::registry.group<T...>();
        }
    };
}
