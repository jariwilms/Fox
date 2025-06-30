#pragma once

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/shader/shader.hpp>

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

        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::Pipeline<gfx::Shader>>
        {
            return _;
        }

    protected:
        Pipeline(const Layout& layout)
            : _{ std::make_shared<impl::Pipeline<gfx::Shader>>(layout) } {}

        std::shared_ptr<impl::Pipeline<gfx::Shader>> _;
    };
}
