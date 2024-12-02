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
            std::shared_ptr<T> vertexShader{};
            std::shared_ptr<T> tessellationControlShader{};
            std::shared_ptr<T> tessellationEvaluationShader{};
            std::shared_ptr<T> geometryShader{};
            std::shared_ptr<T> fragmentShader{};
        };

    protected:
        Pipeline() = default;
    };
}
