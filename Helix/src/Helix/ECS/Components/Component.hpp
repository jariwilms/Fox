#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Entity/Entity.hpp"

namespace hlx
{
    class Component
    {
    public:
        virtual ~Component() = default;

    protected:
        Component() = default;

        template<typename T>
        void find_sibling()
        {

        }

        std::shared_ptr<Entity> m_parent{};
    };
}
