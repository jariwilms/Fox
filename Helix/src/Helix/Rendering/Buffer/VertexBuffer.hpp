#pragma once

#include "stdafx.hpp"

#include "VertexContainer.hpp"
#include "Helix/Core/Library/Interface/IBindable.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
    class VertexBuffer : public VertexContainer, public NonCopyable
    {
    public:
        virtual ~VertexBuffer() = default;

        template<typename T = byte>
        void copy(size_t offset, const std::span<T>& data)
        {
            _copy(offset * sizeof(T), data.size() * sizeof(T), data.data());
        }
        template<typename T = byte>
        std::weak_ptr<std::span<T>> map(VertexContainer::AccessFlag flags)
        {
            if (!m_mappedBuffer.expired()) return m_mappedBuffer;

            auto* buffer = reinterpret_cast<byte*>(_map(flags));
            m_mappedBuffer = std::make_shared<std::span<byte>>(buffer, m_size / sizeof(byte));

            return m_mappedBuffer;
        }
        virtual void unmap()
        {
            m_mappedBuffer.reset();
            _unmap();
        }

    protected:
        VertexBuffer(size_t size)
            : VertexContainer{ size } {}

        std::weak_ptr<std::span<byte>> m_mappedBuffer{};
    };
}
