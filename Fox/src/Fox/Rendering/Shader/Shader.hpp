#pragma once

#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"

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

        auto stage()  const
        {
            return _->stage();
        }
        auto handle() const
        {
            return _->handle();
        }

    protected:
        Shader(Stage stage, std::span<const fox::byte_t> binary)
            : _{ std::make_shared<impl::Shader>(stage, binary) } {}

        std::shared_ptr<impl::Shader> _;
    };
}
