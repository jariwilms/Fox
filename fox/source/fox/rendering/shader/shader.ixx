module;

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/base/shader/shader.hpp>

export module fox.rendering.shader;

import std;

import fox.core.meta;
import fox.core.types;

export namespace fox::gfx
{
    class Shader
    {
    public:
        using Stage = api::Shader::Stage;

        Shader(std::shared_ptr<impl::Shader> _)
            : _{ _ } {}

        static auto create(Stage stage, std::span<const fox::byte_t> binary) -> std::shared_ptr<gfx::Shader>
        {
            return std::make_shared<fox::from_inaccessible_ctor<gfx::Shader>>(stage, binary);
        }

        auto stage () const -> Stage
        {
            return _->stage();
        }
        auto handle() const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl  () const -> std::shared_ptr<impl::Shader>
        {
            return _;
        }

    protected:
        Shader(Stage stage, std::span<const fox::byte_t> binary)
            : _{ std::make_shared<impl::Shader>(stage, binary) } {}

        std::shared_ptr<impl::Shader> _;
    };
}
