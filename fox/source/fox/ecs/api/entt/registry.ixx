export module fox.ecs.api.entt;

import std;
import fox.core.types;
import vendor.entt;

export namespace fox::ecs::api::entt
{
    class registry
    {
    public:
        auto create() -> fox::id_t
        {
            return registry_.create();
        }
        void destroy(fox::id_t id)
        {
            registry_.destroy(id);
        }

        template<typename... T>
        auto has_component(fox::id_t id) -> fox::bool_t
        {
            return registry_.all_of<T...>(id);
        }
        template<typename T, typename... Args>
        auto add_component(fox::id_t id, Args&&... args) -> T&
        {
            return registry_.emplace<T>(id, std::forward<Args>(args)...);
        }
        template<typename T>
        auto get_component(fox::id_t id) -> T&
        {
            return registry_.get<T>(id);
        }
        template<typename T>
        void remove_component(fox::id_t id)
        {
            registry_.remove<T>(id);
        }

        template<typename... T>
        auto view() -> auto
        {
            return registry_.view<T...>();
        }
        template<typename... T>
        auto group() -> auto
        {
            return registry_.group<T...>();
        }

    private:
        ::entt::basic_registry<fox::id_t> registry_;
    };
}
