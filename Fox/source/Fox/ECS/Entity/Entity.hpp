#pragma once

#include <fox/core/types/ecs/ecs.hpp>

namespace fox::ecs
{
    class Entity
    {
    public:
        auto id() const -> fox::id_t
        {
            return id_;
        }

    protected:
        Entity(fox::id_t id)
            : id_{ id } {}

        fox::id_t id_{};
    };
}
