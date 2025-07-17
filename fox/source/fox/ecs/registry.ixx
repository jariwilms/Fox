export module fox.ecs.registry;

import std;
import fox.core.types;
import fox.ecs.api;
import fox.ecs.component;
import vendor.entt;

auto registry = fox::ecs::api::registry_t{};

export namespace fox::registry
{
    auto create() -> fox::id_t
    {
        return ::registry.create();
    }
    void destroy(fox::id_t id)
    {
        ::registry.destroy(id);
    }

    template<typename... T>
    auto has_component   (fox::id_t id) -> fox::bool_t
    {
        return ::registry.all_of<T...>(id);
    }
    template<typename T, typename... Args>
    auto add_component   (fox::id_t id, Args&&... args) -> T&
    {
        return ::registry.emplace<T>(id, std::forward<Args>(args)...);
    }
    template<typename T>
    auto get_component   (fox::id_t id) -> T&
    {
        return ::registry.get<T>(id);
    }
    template<typename T>
    void remove_component(fox::id_t id)
    {
        ::registry.remove<T>(id);
    }

    template<typename... T>
    auto view() -> auto
    {
        return ::registry.view<T...>();
    }
    template<typename... T>
    auto group() -> auto
    {
        return ::registry.group<T...>();
    }
}
