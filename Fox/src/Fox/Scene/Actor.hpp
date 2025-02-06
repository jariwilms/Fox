#pragma once

#include "Fox/ECS/Entity/Entity.hpp"
#include "Fox/ECS/Registry.hpp"
#include "Fox/ECS/Components/Components.hpp"

namespace fox::scn
{
    class Actor : public ecs::Entity
    {
    public:
        Actor()
            : ecs::Entity{ reg::create() }
        {
            add_component<cmp::RelationshipComponent>();
            add_component<cmp::TransformComponent>();
        }
        virtual ~Actor() override
        {
            reg::destroy(m_id);
        }

        template<typename... T>
        bool     has_component() const
        {
            return reg::has_component<T...>(m_id);
        }
        template<typename T, typename... Args>
        T&       add_component(Args&&... args)
        {
            return reg::add_component<T>(m_id, *this, std::forward<Args>(args)...);
        }
        template<typename T>
        T&       get_component()
        {
            return reg::get_component<T>(m_id);
        }
        template<typename T>
        const T& get_component() const
        {
            return reg::get_component<T>(m_id);
        }

        template<typename T>
        void remove_component()
        {
            reg::remove_component<T>(m_id);
        }
        template<> void remove_component<cmp::RelationshipComponent>() = delete;
        template<> void remove_component<cmp::TransformComponent>()    = delete;
    };
}
