#pragma once

#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx
{
    class Pipeline
    {
    public:
        using Layout = impl::Pipeline<gfx::Shader>::Layout;

        static inline auto create(const Layout& layout)
        {
            return std::shared_ptr<Pipeline>(new Pipeline{ layout });
        }

        void bind()
        {
            _->bind();
        }

        auto handle() const
        {
            return _->handle();
        }

    protected:
        Pipeline(const Layout& layout)
            : _{ std::make_shared<impl::Pipeline<gfx::Shader>>(layout) } {}

        std::shared_ptr<impl::Pipeline<gfx::Shader>> _;
    };
}
