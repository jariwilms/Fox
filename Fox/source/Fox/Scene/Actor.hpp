#pragma once

#include "Fox/ECS/Components/Components.hpp"
#include "Fox/ECS/Entity/Entity.hpp"
#include "Fox/ECS/Registry.hpp"

namespace fox::scene
{
    class Actor : public ecs::Entity
    {
    public:
        Actor()
            : ecs::Entity{ reg::create() }
        {
            add_component<ecs::RelationshipComponent>();
            add_component<ecs::TransformComponent>();
        }
        virtual ~Actor()
        {
            reg::destroy(m_id);
        }

        template<typename... T>
        auto has_component() const -> fox::bool_t
        {
            return reg::has_component<T...>(m_id);
        }
        template<typename T, typename... Args>
        auto add_component(Args&&... args) -> T&
        {
            return reg::add_component<T>(m_id, *this, std::forward<Args>(args)...);
        }
        template<typename T>
        auto get_component() -> T&
        {
            return reg::get_component<T>(m_id);
        }
        template<typename T>
        auto get_component() const -> const T&
        {
            return reg::get_component<T>(m_id);
        }

        template<typename T>
        void remove_component()
        {
            reg::remove_component<T>(m_id);
        }
        template<> void remove_component<ecs::RelationshipComponent>() = delete;
        template<> void remove_component<ecs::TransformComponent   >() = delete;
    };
}
