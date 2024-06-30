#pragma once

namespace hlx
{
    class NonMovable
    {
    public:
        NonMovable(NonMovable&&) = delete;
        NonMovable& operator=(NonMovable&&) = delete;

    protected:
        NonMovable() = default;
    };
}
