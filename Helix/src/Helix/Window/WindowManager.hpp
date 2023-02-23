#pragma once

#include "stdafx.hpp"

#include "Window.hpp"

namespace hlx
{
    class WindowManager
    {
    public:
        using iterator = std::unordered_map<std::string, std::shared_ptr<Window>>::iterator;

        WindowManager() = default;
        ~WindowManager() = default;

        static std::shared_ptr<Window> create(const std::string& identifier, const std::string& title, const Vector2u& dimensions);

        static iterator find(const std::string& identifier);

    private:
        static inline std::unordered_map<std::string, std::shared_ptr<Window>> s_windows{};
    };
}
