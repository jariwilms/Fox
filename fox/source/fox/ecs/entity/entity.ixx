export module fox.ecs.entity;

import std;
import fox.core.types;
import fox.ecs.components;
import fox.ecs.registry;

export namespace fox::ecs
{
    class entity
    {
    public:
        auto id() const -> fox::id_t
        {
            return id_;
        }

        template<typename... T>
        auto has_component() const -> fox::bool_t
        {
            return registry::has_component<T...>(id_);
        }
        template<typename T, typename... Args>
        auto add_component(Args&&... args) -> T&
        {
            return registry::add_component<T>(id_, std::forward<Args>(args)...);
        }
        template<typename T>
        auto get_component() -> T&
        {
            return registry::get_component<T>(id_);
        }
        template<typename T>
        auto get_component() const -> const T&
        {
            return registry::get_component<T>(id_);
        }

        template<typename T>
        void remove_component()
        {
            registry::remove_component<T>(id_);
        }
        template<> 
        void remove_component<ecs::relationship_component>() = delete;
        template<> 
        void remove_component<ecs::transform_component   >() = delete;

    protected:
         entity()
            : id_{ registry::create() } {}
         entity(const ecs::entity& other)
             : id_{ other.id_ } {}
         entity(ecs::entity&& other)
             : id_{ std::exchange(other.id_, fox::id_t{})} {}
        ~entity()
        {
            registry::destroy(id_);
        }

    private:
        fox::id_t id_;
    };
}
