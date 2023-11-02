#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Rendering.hpp"

namespace hlx::gfx::test
{
    //template<template<Buffer::Access, typename> typename T, Buffer::Access ACCESS, typename U>
    //std::unique_ptr<VertexBuffer<Buffer::Access::Dynamic, U>> create(u32 count)       requires (std::is_same_v<T<ACCESS, U>, VertexBuffer<ACCESS, U>> && ACCESS == Buffer::Access::Dynamic)
    //{
    //    return std::make_unique<VertexBuffer<Buffer::Access::Dynamic, U>>(count);
    //}
    //template<template<Buffer::Access, typename> typename T, Buffer::Access ACCESS, typename U>
    //std::unique_ptr<VertexBuffer<ACCESS, U>> create(std::span<const U> data)       requires (std::is_same_v<T<ACCESS, U>, VertexBuffer<ACCESS, U>>)
    //{
    //    return std::make_unique<VertexBuffer<ACCESS, U>>(data);
    //}
    //template<template<Buffer::Access> typename T, Buffer::Access ACCESS>
    //std::unique_ptr<IndexBuffer<ACCESS>> create()           requires (std::is_same_v<T<ACCESS>, IndexBuffer<ACCESS>>)
    //{

    //}
    //template<template<typename> typename T, typename U>
    //std::unique_ptr<UniformBuffer<U>> create()              requires (std::is_same_v<T<U>, UniformBuffer<U>>)
    //{

    //}
    //template<template<Buffer::Access, typename> typename T, Buffer::Access ACCESS, typename U> 
    //std::unique_ptr<UniformArrayBuffer<ACCESS, U>> create() requires (std::is_same_v<T<ACCESS, U>, UniformArrayBuffer<ACCESS, U>>)
    //{

    //}
    //template<typename T>
    //std::unique_ptr<VertexArray> create()                   requires (std::is_same_v<T, VertexArray>)
    //{

    //}

    void test()
    {
        auto vbufs = std::make_shared<VertexBuffer<Buffer::Access::Dynamic, float>>(12u);
        VertexLayout layout{};
        VertexArray* vaptr{};

        vaptr->tie(vbufs, layout);
    }
}