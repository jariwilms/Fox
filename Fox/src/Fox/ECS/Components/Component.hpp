#pragma once

namespace hlx
{
    class Entity;
    struct Component
    {
    public:
        virtual ~Component() = default;

        Entity& owner;

    protected:
        Component(Entity& owner)
            : owner{ owner } {}
    };
}
