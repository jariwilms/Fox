export module vendor.glad;

import std;
import <glad/gl.h>;
import vendor.glfw.functions;

export namespace vendor::glad
{
    void initialize()
    {
        if (!::gladLoadGL(vendor::glfw::function_address)) throw std::runtime_error{ "Failed to initialize GLAD!" };
    }
}
