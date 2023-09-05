#pragma once

#include "stdafx.hpp"

#include <entt/entt.hpp>

namespace hlx
{
    class Registry
    {
    public:
        static void init()
        {

        }

        static Id create()
        {
            return s_registry.create();
        }
        static void destroy(Id id)
        {
            s_registry.destroy(id);
        }

        template<typename... T>
        static bool has_component(Id id)
        {
            //static_assert(std::is_base_of_v<Component, T>);
            return s_registry.all_of<T...>(id);
        }
        template<typename T, typename... Args>
        static T& add_component(Id id, Args&&... args)
        {
            return s_registry.emplace<T>(id, std::forward<Args>(args)...);
        }
        template<typename T>
        static T& get_component(Id id)
        {
            return s_registry.get<T>(id);
        }
        template<typename T>
        static void remove_component(Id id)
        {
            s_registry.remove<T>(id);
        }

        template<typename... T>
        static auto view() //TODO: wrapper for entity group (using my_view = entt::basic_view ofzoiets)
        {
            return s_registry.view<T...>();
        }
        template<typename... T>
        static auto group()
        {
            return s_registry.group<T...>();
        }

    private:
        static inline entt::basic_registry<Id> s_registry{};
    };
}
