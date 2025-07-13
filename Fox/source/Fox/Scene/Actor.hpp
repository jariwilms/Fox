#pragma once

#include <stdafx.hpp>

#include <fox/ecs/registry.hpp>
#include <fox/ecs/components/components.hpp>

import fox.core.types.fundamental;
//import fox.ecs.components;
import fox.ecs.entity;

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
            registry::destroy(id_);
        }

        template<typename... T>
        auto has_component() const -> fox::bool_t
        {
            return registry::has_component<T...>(id_);
        }
        template<typename T, typename... Args>
        auto add_component(Args&&... args) -> T&
        {
            return registry::add_component<T>(id_, *this, std::forward<Args>(args)...);
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
        template<> void remove_component<ecs::RelationshipComponent>() = delete;
        template<> void remove_component<ecs::TransformComponent   >() = delete;
    };
}
