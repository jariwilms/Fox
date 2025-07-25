export module fox.ecs.registry;

import std;
import fox.core.types;
import fox.ecs.api;

export namespace fox::ecs::registry
{
    auto create() -> fox::id_t
    {
        return api::registry->create();
    }
    void destroy(fox::id_t id)
    {
        api::registry->destroy(id);
    }

    template<typename... T>
    auto has_component   (fox::id_t id) -> fox::bool_t
    {
        return api::registry->has_component<T...>(id);
    }
    template<typename T, typename... Args>
    auto add_component   (fox::id_t id, Args&&... args) -> T&
    {
        return api::registry->add_component<T>(id, std::forward<Args>(args)...);
    }
    template<typename T>
    auto get_component   (fox::id_t id) -> T&
    {
        return api::registry->get_component<T>(id);
    }
    template<typename T>
    void remove_component(fox::id_t id)
    {
        api::registry->remove_component<T>(id);
    }

    template<typename... T>
    auto view() -> auto
    {
        return api::registry->view<T...>();
    }
    template<typename... T>
    auto group() -> auto
    {
        return api::registry->group<T...>();
    }
}
