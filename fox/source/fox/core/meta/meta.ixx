export module fox.core.meta;
export import fox.core.meta.concepts;

import std;

export namespace fox::meta
{
    template<typename T>
    struct from_inaccessible_ctor final : public T
    {
        template<typename... Args> requires (!std::same_as<meta::from_inaccessible_ctor<T>, std::remove_cvref_t<Args>> && ...)
        explicit from_inaccessible_ctor(Args&&... args)
            : T{ std::forward<Args>(args)... } {}
    };

    template<typename... Ts>
    struct overload : Ts... { using Ts::operator()...; };
}
