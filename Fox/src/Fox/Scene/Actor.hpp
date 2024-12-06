#pragma once

#include "Fox/ECS/Entity/Entity.hpp"
#include "Fox/ECS/Registry.hpp"
#include "Fox/ECS/Components/RelationshipComponent.hpp"
#include "Fox/ECS/Components/TransformComponent.hpp"

namespace fox
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
        virtual ~Actor() override
        {
            reg::destroy(m_id);
        }

        template<typename... T>
        bool has_component()
        {
            return reg::has_component<T...>(m_id);
        }
        template<typename T, typename... Args>
        T&   add_component(Args&&... args)
        {
            return reg::add_component<T>(m_id, *this, std::forward<Args>(args)...);
        }
        template<typename T>
        T&   get_component()
        {
            return reg::get_component<T>(m_id);
        }
        template<typename T>
        void remove_component()
        {
            reg::remove_component<T>(m_id);
        }
        template<> void remove_component<ecs::RelationshipComponent>() = delete;
        template<> void remove_component<ecs::TransformComponent>()    = delete;
    };
}
