export module fox.core.meta;
export import fox.core.meta.concepts;

import std;

export namespace fox::meta
{
    template<typename T>
    struct from_inaccessible_ctor final : public T
    {
        template<typename... Args>
        explicit from_inaccessible_ctor(std::in_place_t, Args&&... args)
            : T{ std::forward<Args>(args)... } {}

        from_inaccessible_ctor(const meta::from_inaccessible_ctor<T>& )          = delete;
        from_inaccessible_ctor(      meta::from_inaccessible_ctor<T>&&) noexcept = delete;
    };

    template<typename... Ts>
    struct overload : Ts... { using Ts::operator()...; };
}
