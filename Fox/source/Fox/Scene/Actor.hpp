#pragma once

#include <utility>

#include <fox/ecs/components/components.hpp>
#include <fox/ecs/entity/entity.hpp>
#include <fox/ecs/registry.hpp>

namespace fox::scene
{
    class Actor : public ecs::Entity
    {
    public:
        Actor()
            : ecs::Entity{ registry::create() }
        {
            add_component<ecs::RelationshipComponent>();
            add_component<ecs::TransformComponent>();
        }
        virtual ~Actor()
        {
            registry::destroy(m_id);
        }

        template<typename... T>
        auto has_component() const -> fox::bool_t
        {
            return registry::has_component<T...>(m_id);
        }
        template<typename T, typename... Args>
        auto add_component(Args&&... args) -> T&
        {
            return registry::add_component<T>(m_id, *this, std::forward<Args>(args)...);
        }
        template<typename T>
        auto get_component() -> T&
        {
            return registry::get_component<T>(m_id);
        }
        template<typename T>
        auto get_component() const -> const T&
        {
            return registry::get_component<T>(m_id);
        }

        template<typename T>
        void remove_component()
        {
            registry::remove_component<T>(m_id);
        }
        template<> void remove_component<ecs::RelationshipComponent>() = delete;
        template<> void remove_component<ecs::TransformComponent   >() = delete;
    };
}
