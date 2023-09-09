#pragma once

#include "stdafx.hpp"

#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformArrayBuffer.hpp"
#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"
#include "Helix/Rendering/RenderSettings.hpp"

#include "Helix/Rendering/Model/Model.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"

namespace hlx
{
    class OpenGLRenderer : public RendererAPI
    {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer() = default;

        void start(const RenderInfo& renderInfo) override;
        void finish() override;

        void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform) override;

    private:
        void swap_buffer()
        {
            static unsigned int bufferIndex{};
            static const unsigned int bufferCount = m_ppBuffers.size();

            ++bufferIndex %= bufferCount;

        }

        std::shared_ptr<FrameBufferMultisample> m_gBufferMultisample{};
        std::shared_ptr<FrameBuffer> m_gBuffer{};
        std::array<std::shared_ptr<FrameBuffer>, 2> m_ppBuffers{};

        std::unordered_map<std::string, std::shared_ptr<Pipeline>> m_pipelines{}; 

        std::shared_ptr<UniformBuffer<UMatrices>> m_matricesBuffer{};
        std::shared_ptr<UniformBuffer<UMaterial>> m_materialBuffer{};          //TODO: Convert UniformArrayBuffer
        std::shared_ptr<UniformArrayBuffer<ULight>> m_lightBuffer{};
        std::shared_ptr<UniformBuffer<UCamera>> m_cameraBuffer{};
    };
}
