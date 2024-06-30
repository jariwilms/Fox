#pragma once

#include "stdafx.hpp"

#include "Window.hpp"

namespace hlx
{
    class WindowManager
    {
    public:
        WindowManager() = default;
        ~WindowManager() = default;

        static std::shared_ptr<Window> create(const std::string& identifier, const std::string& title, const Vector2u& dimensions);

        static std::shared_ptr<Window> find(const Window* const instance);
        static std::shared_ptr<Window> find(const std::string& identifier);
        static std::shared_ptr<Window> find(size_t identifier);

    private:
        static inline std::unordered_map<size_t, std::shared_ptr<Window>> s_windows{};
    };
}
