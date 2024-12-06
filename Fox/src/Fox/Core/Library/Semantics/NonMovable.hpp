#pragma once

namespace fox
{
    class NonMovable
    {
    public:
        NonMovable(NonMovable&&) = delete;
        NonMovable& operator=(NonMovable&&) = delete;

    protected:
        NonMovable()  = default;
        virtual ~NonMovable() = default;
    };
}
