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
        static auto create() -> fox::id_t
        {
            return api::registry.create();
        }
        static void destroy(fox::id_t id)
        {
            api::registry.destroy(id);
        }

        template<typename... T>
        static auto has_component(fox::id_t id) -> fox::bool_t
        {
            return api::registry.all_of<T...>(id);
        }
        template<typename T, typename... Args>
        static auto add_component(fox::id_t id, Args&&... args) -> T&
        {
            return api::registry.emplace<T>(id, std::forward<Args>(args)...);
        }
        template<typename T>
        static auto get_component(fox::id_t id) -> T&
        {
            return api::registry.get<T>(id);
        }
        template<typename T>
        static void remove_component(fox::id_t id)
        {
            api::registry.remove<T>(id);
        }

        template<typename... T>
        static auto view()
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
