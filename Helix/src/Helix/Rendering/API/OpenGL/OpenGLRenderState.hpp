#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RenderStateAPI.hpp"

namespace hlx
{
    class OpenGLRenderState : public RenderStateAPI
    {
    public:
        static void init()
        {

        }

        static inline Vector4f clearColor{};
        static inline GLuint boundVertexArrayId{};
        static inline GLuint boundVertexBufferId{};
        static inline GLuint boundIndexBufferId{};
        static inline GLuint boundFrameBufferReadTargetId{};
        static inline GLuint boundFrameBufferWriteTargetId{};
        static inline std::unordered_map<unsigned int, GLuint> slotToBoundTextureMapId{};
    };
}