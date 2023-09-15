#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"

namespace hlx::exp
{
    //enum class Wrapping
    //{
    //    ClampToEdge,
    //    ClampToBorder,

    //    MirroredRepeat,
    //    Repeat,
    //    MirroredClampToEdge,
    //};

    //template<size_t D>
    //class Texture : public IBindable
    //{
    //public:
    //    Texture() = default;

    //    template<size_t Cond = D>
    //    typename std::enable_if_t<(Cond >= 1), Wrapping> wrapping_r()
    //    {
    //        return m_wrappings[0];
    //    }
    //    template<size_t Cond = D>
    //    typename std::enable_if_t<(Cond >= 2), Wrapping> wrapping_s()
    //    {
    //        return m_wrappings[1];
    //    }
    //    template<size_t Cond = D>
    //    typename std::enable_if_t<(Cond >= 3), Wrapping> wrapping_t()
    //    {
    //        return m_wrappings[2];
    //    }

    //    typename std::enable_if_t<true, float> val{};

    //protected:
    //    std::array<Wrapping, D> m_wrappings{};
    //};

    //using Texture2D = Texture<2>;

    //void test()
    //{
    //    Texture2D t{};
    //    //t.val = 2.0f;
    //}
}
