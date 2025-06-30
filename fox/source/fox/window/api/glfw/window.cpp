#include <stdafx.hpp>

#include <fox/rendering/graphics_api/opengl/context/context.hpp>
#include <fox/rendering/graphics_api/opengl/opengl.hpp>
#include <fox/window/api/glfw/window.hpp>

namespace fox::interface::api::glfw
{
    Window::Window(const std::string& name, const fox::Vector2u& dimensions)
        : name_{ name }, dimensions_{ dimensions }, mode_{ Mode::Windowed }
    {
        if (glfwInit() != GLFW_TRUE) throw std::runtime_error{ "Failed to initialize GLFW!" };

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4                       );
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6                       );
        glfwWindowHint(GLFW_OPENGL_PROFILE       , GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_REFRESH_RATE         , GLFW_DONT_CARE          );
#ifdef FOX_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT , fox::True               );
#endif

        



        instance_ = glfwCreateWindow(static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y), name_.c_str(), nullptr, nullptr);
        if (!instance_) throw std::runtime_error{ "Failed to create GLFW window!" };
        
        glfwMakeContextCurrent(instance_);
        glfwSwapInterval(0);

        auto version = gladLoadGL(glfwGetProcAddress);
        if (!version) throw std::runtime_error{ "Failed to initialize GLAD!" };

        input::api::handler = std::make_shared<input::api::glfw::InputHandler>();
        context_            = std::make_shared<Context>(std::shared_ptr<Window>(this, [](const auto* context) {  }), input::api::handler);





        using namespace gfx::api;

        gl::Context::init();
        static const auto& context = context_;
            
        glfwSetErrorCallback          (           [](fox::int32_t error , const fox::char_t* description)
            {
                std::print("[GLFW_ERROR] {0}: {1}\n", error, description);
            });
        glfwSetKeyCallback            (instance_, [](GLFWwindow*  window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action  , fox::int32_t mods  ) 
            { 
                context->input->glfw_input_key_callback(window, key, scancode, action, mods); 
            });
        glfwSetMouseButtonCallback    (instance_, [](GLFWwindow*  window, fox::int32_t   button, fox::int32_t   action  , fox::int32_t mods    )
            {
                context->input->glfw_input_button_callback(window, button, action, mods);
            });
        glfwSetCursorPosCallback      (instance_, [](GLFWwindow*  window, fox::float64_t x     , fox::float64_t y       )
            {
                context->input->glfw_input_cursor_callback(window, x, y);
            });
        glfwSetScrollCallback         (instance_, [](GLFWwindow*  window, fox::float64_t x     , fox::float64_t y       )
            {
                context->input->glfw_input_scroll_callback(window, x, y);
            });
        glfwSetFramebufferSizeCallback(instance_, [](GLFWwindow*  window, fox::int32_t   width , fox::int32_t   height  )
            {
                gl::viewport(gl::Vector2u{ static_cast<gl::uint32_t>(width), static_cast<gl::uint32_t>(height) });
            });
    }
    Window::~Window()
    {
        glfwDestroyWindow(instance_);
        glfwTerminate();
    }
}
