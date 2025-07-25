export module fox.rendering.shader;

import std;
import fox.core.meta;
import fox.core.types;
import fox.rendering.api;
import fox.rendering.base.shader;

export namespace fox::gfx
{
    class shader
    {
    public:
        using stage_e = api::shader::stage_e;

        explicit shader(std::shared_ptr<impl::shader> _)
            : _{ _ } {}

        static auto create(stage_e stage_e, std::span<const fox::byte_t> binary) -> std::shared_ptr<gfx::shader>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::shader>>(std::in_place_t{}, stage_e, binary);
        }

        auto stage () const -> stage_e
        {
            return _->stage();
        }
        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::shader>
        {
            return _;
        }

    protected:
        shader(stage_e stage_e, std::span<const fox::byte_t> binary)
            : _{ std::make_shared<impl::shader>(stage_e, binary) } {}

    private:
        std::shared_ptr<impl::shader> _;
    };
}
