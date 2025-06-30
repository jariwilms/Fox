#pragma once

#include <fox/rendering/api/api.hpp>

namespace fox::gfx
{
    class Shader
    {
    public:
        using Stage = api::Shader::Stage;

        static inline auto create(Stage stage, std::span<const fox::byte_t> binary)
        {
            return std::shared_ptr<Shader>(new Shader{ stage, binary });
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
