#include "stdafx.hpp"

#include "WindowManager.hpp"
#include "API/GLFW/GLFWWindow.hpp"

namespace hlx
{
    std::shared_ptr<Window> WindowManager::create(const std::string& identifier, const std::string& title, const Vector2u& dimensions)
    {
        const auto window = std::make_shared<GLFWWindow>(title, dimensions);
        s_windows.emplace(identifier, window);

        return window;
    }

    WindowManager::iterator WindowManager::find(const std::string& identifier)
    {
        return s_windows.find(identifier);
    }
}
