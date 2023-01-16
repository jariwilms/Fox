#pragma once

namespace hlx
{
    class NonCopyable
    {
    public:
        virtual ~NonCopyable() = default;

        NonCopyable(const NonCopyable& other) = delete;
        NonCopyable& operator=(const NonCopyable& other) = delete;

    protected:
        NonCopyable() = default;
    };
}
