#pragma once

#include "stdafx.hpp"

namespace hlx
{
    template<class _Ty, size_t _Size>
    class CyclicBuffer
    {
    public:
        using value_type      = _Ty;
        using size_type       = size_t;
        using difference_type = ptrdiff_t;
        using pointer         = _Ty*;
        using const_pointer   = const _Ty*;
        using reference       = _Ty&;
        using const_reference = const _Ty&;

        using iterator       = std::array<_Ty, _Size>::iterator;
        using const_iterator = std::array<_Ty, _Size>::const_iterator;

        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        CyclicBuffer() = default;

        constexpr void fill(const _Ty& value)
        {
            m_array.fill(value);
        }

        constexpr iterator begin() noexcept
        {
            return m_array.begin();
        }
        constexpr const_iterator begin() const noexcept
        {
            return m_array.begin();
        }
        constexpr iterator end() noexcept
        {
            return m_array.end();
        }
        constexpr const_iterator end() const noexcept
        {
            return m_array.end();
        }

        constexpr reverse_iterator rbegin() noexcept
        {
            return reverse_iterator{ end() };
        }
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator{ end() };
        }
        constexpr reverse_iterator rend() noexcept
        {
            return reverse_iterator{ begin() };
        }
        constexpr const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator{ begin() };
        }

        constexpr const_iterator cbegin() const noexcept
        {
            return begin();
        }
        constexpr const_iterator cend() const noexcept
        {
            return end();
        }
        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return rbegin();
        }
        constexpr const_reverse_iterator crend() const noexcept
        {
            return rend();
        }

        constexpr size_t size() const noexcept
        {
            return m_array.size();
        }

        constexpr bool empty() const noexcept
        {
            return false;
        }

        constexpr reference at(size_type index)
        {
            return m_array.at(index);
        }
        constexpr const_reference at(size_type index) const
        {
            return m_array.at(index);
        }

        constexpr void push_back(const _Ty& value)
        {
            m_array.at(m_index) = value;
            shift();
        }

        constexpr reference operator[](size_type offset) noexcept
        {
            return m_array[offset];
        }
        constexpr const_reference operator[](size_type offset) const noexcept
        {
            return m_array[offset];
        }

        constexpr _Ty* data() noexcept
        {
            return m_array.data();
        }
        constexpr const _Ty* data() const noexcept
        {
            return m_array.data();
        }

    private:
        constexpr void shift()
        {
            ++m_index %= m_array.size();
        }

        std::array<_Ty, _Size> m_array{};
        size_t m_index{};
    };
}
