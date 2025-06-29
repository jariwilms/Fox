#pragma once

#include <stdafx.hpp>

#include <fox/window/window.hpp>

namespace fox::wnd
{
    class WindowManager
    {
    public:
        WindowManager() = default;
        ~WindowManager() = default;

        static std::shared_ptr<api::glfw::Window> create(const std::string& identifier, const std::string& title, const Vector2u& dimensions);

        static std::shared_ptr<api::Window> find(const api::Window* const instance);
        static std::shared_ptr<api::Window> find(const std::string& identifier);
        static std::shared_ptr<api::Window> find(size_t identifier);

    private:
        static inline std::unordered_map<size_t, std::shared_ptr<api::glfw::Window>> s_windows{};
    };
}
