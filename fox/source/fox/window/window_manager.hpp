#pragma once

#include <stdafx.hpp>

#include <fox/window/window.hpp>

namespace fox::wnd
{
    class WindowManager
    {
    public:
        static auto create(const std::string& identifier, const std::string& title, const fox::Vector2u& dimensions) -> std::shared_ptr<wnd::Window>
        {
            auto window = wnd::Window::create(title, dimensions);
            windows_.emplace(std::hash<std::string>{}(identifier), window);

            return window;
        }

        static auto find(const wnd::Window* const instance) -> std::shared_ptr<wnd::Window>
        {
            return std::ranges::find_if(windows_, [instance](const auto& _) -> fox::bool_t
                {
                    return _.second.get() == instance;
                })->second;
        }
        static auto find(const std::string& identifier) -> std::shared_ptr<wnd::Window>
        {
            return windows_.at(std::hash<std::string>{}(identifier));
        }

    private:
        static inline std::unordered_map<fox::hash_t, std::shared_ptr<wnd::Window>> windows_{};
    };
}
