//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
//#include "Helix/Rendering/Layout/VertexLayout.hpp"
//
//namespace hlx
//{
//	struct OpenGLVertexLayout : public VertexLayout
//	{
//	public:
//		OpenGLVertexLayout() = default;
//		~OpenGLVertexLayout() = default;
//		
//	protected:
//        void specify_bool(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_BOOL, count, sizeof(bool));
//            m_stride += count * sizeof(bool);
//        }
//        void specify_char(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_BYTE, count, sizeof(char));
//            m_stride += count * sizeof(char);
//        }
//        void specify_unsigned_char(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_UNSIGNED_BYTE, count, sizeof(unsigned char));
//            m_stride += count * sizeof(unsigned char);
//        }
//        void specify_short(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_SHORT, count, sizeof(short));
//            m_stride += count * sizeof(short);
//        }
//        void specify_unsigned_short(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_UNSIGNED_SHORT, count, sizeof(unsigned short));
//            m_stride += count * sizeof(unsigned short);
//        }
//        void specify_int(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_INT, count, sizeof(int));
//            m_stride += count * sizeof(int);
//        }
//        void specify_unsigned_int(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_UNSIGNED_INT, count, sizeof(unsigned int));
//            m_stride += count * sizeof(unsigned int);
//        }
//        void specify_float(unsigned int count) override
//        {
//            m_attributes.emplace_back(GL_FLOAT, count, sizeof(float));
//            m_stride += count * sizeof(float);
//        }
//        void specify_double(unsigned int count) override
//		{
//			m_attributes.emplace_back(GL_DOUBLE, count, sizeof(double));
//			m_stride += count * sizeof(double);
//		}
//	};
//}
