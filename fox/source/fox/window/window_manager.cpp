#include <stdafx.hpp>

#include <fox/window/window.hpp>
#include <fox/window/window_manager.hpp>

namespace fox::wnd
{
    std::shared_ptr<api::glfw::Window> WindowManager::create(const std::string& identifier, const std::string& title, const Vector2u& dimensions)
    {
        const auto& window = std::make_shared<api::glfw::Window>(title, dimensions);
        s_windows.emplace(std::hash<std::string>{}(identifier), window);

        return window;
    }

    std::shared_ptr<api::Window> WindowManager::find(const api::Window* const instance)
    {
        const auto& pred = [instance](const std::unordered_map<size_t, std::shared_ptr<api::Window>>::value_type value) -> bool
        {
            return value.second.get() == instance;
        };
        if (const auto& it = std::find_if(s_windows.begin(), s_windows.end(), pred); it != s_windows.end()) return it->second;
        throw std::runtime_error{ "Invalid window pointer!" };
    }
    std::shared_ptr<api::Window> WindowManager::find(size_t identifier)
    {
        if (const auto& it = s_windows.find(identifier); it != s_windows.end()) return it->second;
        throw std::runtime_error{ "Invalid window identifier!" };
    }
    std::shared_ptr<api::Window> WindowManager::find(const std::string& identifier)
    {
        if (const auto& it = s_windows.find(std::hash<std::string>{}(identifier)); it != s_windows.end()) return it->second;
        throw std::runtime_error{ "Invalid window identifier!" };
    }
}
