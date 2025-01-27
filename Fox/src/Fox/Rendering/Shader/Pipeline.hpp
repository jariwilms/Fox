#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
    class Pipeline
    {
    public:
        template<typename T>
        struct Layout
        {
            std::shared_ptr<T> vertex{};
            std::shared_ptr<T> tessellationControl{};
            std::shared_ptr<T> tessellationEvaluation{};
            std::shared_ptr<T> geometry{};
            std::shared_ptr<T> fragment{};
        };

    protected:
        Pipeline() = default;
    };
}
