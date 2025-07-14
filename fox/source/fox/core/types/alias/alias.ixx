export module fox.core.types.alias;

import std;

export namespace fox
{
    template<typename T, typename U>
    class alias_t
    {
    public:
                 alias_t(U value = {})
            : value_{ static_cast<T>(value) } {}
        explicit alias_t(std::underlying_type_t<U> value = {})
            : value_{ static_cast<T>(value) } {}

        operator auto() const
        {
            return static_cast<U>(value_);
        }

    private:
        T value_;
    };
}
