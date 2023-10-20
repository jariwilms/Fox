#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace gfx_test
{
    //namespace imp
    //{
    //    class Renderer
    //    {
    //    public:
    //        virtual void accept(def::Texture2D) = 0;
    //    };

    //    template<GraphicsAPI G>
    //    class GRenderer : public Renderer
    //    {
    //    public:
    //    };
    //    template<>
    //    class GRenderer<GraphicsAPI::OpenGL> : public Renderer
    //    {
    //    public:
    //        void accept(def::Texture2D t2d) override
    //        {
    //            std::cout << "OpenGLRenderer\n";
    //            t2d.print();
    //        }
    //    };
    //    template<>
    //    class GRenderer<GraphicsAPI::Vulkan> : public Renderer
    //    {
    //    public:
    //        void accept(def::Texture2D t2d) override
    //        {
    //            std::cout << "VulkanRenderer\n";
    //            t2d.print();
    //        }
    //    };
    //}

    //namespace def
    //{
    //    using Renderer = imp::GRenderer<GRAPHICS_API>;
    //}
}
