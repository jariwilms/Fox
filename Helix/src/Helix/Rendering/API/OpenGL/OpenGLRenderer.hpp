#pragma once

#include "stdafx.hpp"

#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformArrayBuffer.hpp"
#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"
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

        void render(const std::shared_ptr<const Model> model, const Transform& transform) override;

    private:
        std::array<std::shared_ptr<FrameBuffer>, 2> m_gBuffers{};
        bool m_pingpong{ false };

        std::unordered_map<std::string, std::shared_ptr<Pipeline>> m_pipelines{}; 
        std::unordered_map<std::string, std::shared_ptr<Pipeline>> m_postProcessingPipelines{};

        std::shared_ptr<UniformBuffer<UMatrices>> m_matricesBuffer{};
        std::shared_ptr<UniformBuffer<UMaterial>> m_materialBuffer{};          //TODO: Convert UniformArrayBuffer
        std::shared_ptr<UniformArrayBuffer<ULight>> m_lightBuffer{};
        std::shared_ptr<UniformBuffer<UCamera>> m_cameraBuffer{};              //TODO: Remove?

        RenderInfo m_renderInfo;
    };
}
