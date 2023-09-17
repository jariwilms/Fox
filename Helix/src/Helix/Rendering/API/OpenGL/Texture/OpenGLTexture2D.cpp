#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
    OpenGLTexture2D::OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
		: Texture2D{ format, filter, wrapping, dimensions }
    {
		m_internalTarget    = GL_TEXTURE_2D;
        m_internalFormat    = OpenGL::texture_format(m_format);
		m_internalMinFilter = OpenGL::texture_min_filter(m_filter);
		m_internalMagFilter = OpenGL::texture_mag_filter(m_filter);
		m_internalWrapping  = OpenGL::texture_wrapping(m_wrapping);

        glCreateTextures(m_internalTarget, 1, &m_internalId);
        glTextureParameteri(m_internalId, GL_TEXTURE_MIN_FILTER, m_internalMinFilter);
        glTextureParameteri(m_internalId, GL_TEXTURE_MAG_FILTER, m_internalMagFilter);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_S, m_internalWrapping);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_T, m_internalWrapping);
		glTextureStorage2D(m_internalId, m_mipLevels, m_internalFormat, m_dimensions.x, m_dimensions.y);
    }
    OpenGLTexture2D::OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components dataComponents, const std::type_info& dataType, std::span<const byte> data)
        : OpenGLTexture2D{ format, filter, wrapping, dimensions }
    {
        _copy(dataComponents, dataType, data);
    }
    OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_internalId);
	}

	void OpenGLTexture2D::bind(unsigned int slot) const
    {
		const auto& pair = s_slotToIdMap.try_emplace(slot, 0);
		if (pair.first->second == m_internalId) return;

		glBindTextureUnit(slot, m_internalId);
		s_slotToIdMap.at(slot) = m_internalId;
		s_idToSlotMap.insert_or_assign(m_internalId, slot);
	}
	void OpenGLTexture2D::unbind() const
	{
		const auto& it = s_idToSlotMap.find(m_internalId);
		if (it == s_idToSlotMap.end()) return;

		const auto& slot = it->first;
		glBindTextureUnit(slot, 0);
		s_slotToIdMap.at(slot) = 0;
		s_idToSlotMap.at(m_internalId) = 0;
	}
	bool OpenGLTexture2D::is_bound() const
	{
		const auto& it = s_idToSlotMap.find(m_internalId);
		if (it == s_idToSlotMap.end()) return false;

		return it->first != 0;
	}
	
	void OpenGLTexture2D::_copy(Components dataComponents, const std::type_info& dataType, std::span<const byte> data)
	{
		_copy_range(m_dimensions, Vector2u{ 0u, 0u }, dataComponents, dataType, data);
	}
	void OpenGLTexture2D::_copy_range(const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, const std::type_info& dataType, std::span<const byte> data)
	{
        if (data.empty()) return;

        const auto& format    = OpenGL::texture_format(dataComponents);
        const auto& type      = OpenGL::type_enum(dataType.hash_code());
		const auto& totalSize = offset + dimensions;
		if (glm::any(glm::greaterThan(m_dimensions, totalSize))) throw std::invalid_argument{ "The total size exceeds texture bounds!" };
		
		glTextureSubImage2D(m_internalId, 0, offset.x, offset.y, dimensions.x, dimensions.y, format, type, data.data());
		if (m_mipLevels > 1) glGenerateTextureMipmap(m_internalId);
	}
}
