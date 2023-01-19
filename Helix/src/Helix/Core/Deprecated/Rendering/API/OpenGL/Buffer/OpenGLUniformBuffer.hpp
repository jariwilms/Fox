//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
//#include "Helix/Rendering/Buffer/Layout/UniformBuffer.hpp"
//
//namespace hlx
//{
//    class OpenGLUniformBuffer : public UniformBuffer
//    {
//    public:
//        OpenGLUniformBuffer(size_t size);
//        OpenGLUniformBuffer(size_t size, const void* data);
//        ~OpenGLUniformBuffer();
//
//        void bind() const override;
//        void bind_base(unsigned int index) override;
//        void bind_range(unsigned int index, size_t size, size_t offset) override;
//        void unbind() const override;
//        bool is_bound() const override;
//
//    protected:
//        void _copy(size_t size, size_t offset, const void* data) override;
//
//        GLenum m_internalTarget{ GL_UNIFORM_BUFFER };
//    };
//}
