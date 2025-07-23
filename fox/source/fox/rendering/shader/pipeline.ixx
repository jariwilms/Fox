export module fox.rendering.pipeline;

import std;
import fox.core.meta;
import fox.core.types;
import fox.rendering.api;
import fox.rendering.shader;

export namespace fox::gfx
{
    class pipeline
    {
    public:
        using layout_t = impl::Pipeline<gfx::shader>::Layout;

        explicit pipeline(std::shared_ptr<impl::Pipeline<gfx::shader>> _)
            : _{ _ } {}

        static auto create(const layout_t& layout) -> std::shared_ptr<gfx::pipeline>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::pipeline>>(std::in_place_t{}, layout);
        }

        void bind()
        {
            _->bind();
        }

        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::Pipeline<gfx::shader>>
        {
            return _;
        }

    protected:
        pipeline(const layout_t& layout)
            : _{ std::make_shared<impl::Pipeline<gfx::shader>>(layout) } {}

    private:
        std::shared_ptr<impl::Pipeline<gfx::shader>> _;
    };
}
