#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"

namespace hlx::gfx::api
{
    class Buffer
    {
    public:
        enum class Usage
        {
            Static,
            Dynamic,
        };
        enum class Type
        {
            Vertex,
            Index,

            Uniform,
            UniformArray, 
        };

        Buffer(size_t size)
            : m_size{ size } {}

        size_t size() const
        {
            return m_size;
        }

    protected:
        size_t m_size{};
    };

    template<GraphicsAPI, Buffer::Type, typename>
    class GBuffer;
}
