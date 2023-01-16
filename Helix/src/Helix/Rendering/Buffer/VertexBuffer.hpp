#pragma once

#include "stdafx.hpp"

#include "VertexContainer.hpp"
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
            auto* buffer = reinterpret_cast<T*>(_map(flags));
            m_isMapped = true;

            return std::make_shared<std::span<T>>(buffer, m_size / sizeof(T));
        }
        virtual void unmap()
        {
            _unmap();
            m_isMapped = false;
        }

        bool is_mapped() const
        {
            return m_isMapped;
        }

    protected:
        VertexBuffer(size_t size)
            : VertexContainer{ size } {}

        bool m_isMapped{};
    };
}
