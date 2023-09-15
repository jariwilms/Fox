#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
	class OpenGLTexture2D: public Texture2D
	{
	public:
		OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions);
		OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components dataComponents, const std::type_info& dataType, std::span<const byte> data);
		~OpenGLTexture2D() override;
		
		void bind(unsigned int slot) const override;
		void unbind()                const override;
		bool is_bound()              const override;
		
        void _copy(Components dataComponents, const std::type_info& typeInfo, std::span<const byte> data) override;
        void _copy_range(const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, const std::type_info& dataType, std::span<const byte> data) override;

		GLuint internal_id()         const
		{
			return m_internalId;
		}
		GLenum internal_target()     const
		{
			return m_internalTarget;
		}
		GLenum internal_format()     const
		{
			return m_internalFormat;
		}
		GLenum internal_min_filter() const
		{
			return m_internalMinFilter;
		}
		GLenum internal_mag_filter() const
		{
			return m_internalMagFilter;
		}
		GLenum internal_wrapping()   const
		{
			return m_internalWrapping;
		}

	private:
		GLuint m_internalId{};
		GLenum m_internalTarget{};
		GLenum m_internalFormat{};
		GLenum m_internalMinFilter{};
		GLenum m_internalMagFilter{};
		GLenum m_internalWrapping{};

		static inline std::unordered_map<unsigned int, GLenum> s_slotToIdMap{};
		static inline std::unordered_map<GLenum, unsigned int> s_idToSlotMap{};
	};
}
