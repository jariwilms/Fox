export module fox.rendering.pipeline;

import std;
import fox.core.meta;
import fox.core.types;
import fox.rendering.api;
import fox.rendering.shader;

export namespace fox::gfx
{
    class Pipeline
    {
    public:
        using Layout = impl::Pipeline<gfx::Shader>::Layout;

        explicit Pipeline(std::shared_ptr<impl::Pipeline<gfx::Shader>> _)
            : _{ _ } {}

        static auto create(const Layout& layout) -> std::shared_ptr<gfx::Pipeline>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::Pipeline>>(std::in_place_t{}, layout);
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

    private:
        std::shared_ptr<impl::Pipeline<gfx::Shader>> _;
    };
}
