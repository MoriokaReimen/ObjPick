/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/Window.hpp"
#include <exception>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>


static void error_callback(int error, const char* description)
{
    spdlog::error("GLFW Error {}:{}", error, description);
}

namespace RenderLib
{
Window::Window(entt::registry& registry)
    : IModule(registry)
{
    Context ctx;
    registry_.ctx().emplace<Context>(ctx);
    spdlog::info("Window Module Created");
}

Window::~Window()
{
    spdlog::info("Window Finalized");
    auto& window = registry_.ctx().get<Context>().window;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::init()
{
    spdlog::info("Window Initialized");

    /* init glfw */
    if(!glfwInit()) {
        spdlog::error("Failed to initialize OpenGL context");
        throw std::runtime_error("Failed to initialize glfw");
    }

    glfwSetErrorCallback(error_callback);

    /* Create Window */
    constexpr int WIDTH = 640;
    constexpr int HEIGHT = 480;
    auto& window = registry_.ctx().get<Context>().window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "GL Sample", NULL, NULL);
    glfwMakeContextCurrent(window);

    /* Load OpenGL */
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        spdlog::error("Failed to initialize OpenGL context");
        throw std::runtime_error("Failed to initialize OpenGL context");
    }
    spdlog::info("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));


}

void Window::update()
{
    auto& window = registry_.ctx().get<Context>().window;
    auto& width = registry_.ctx().get<Context>().width;
    auto& height = registry_.ctx().get<Context>().height;
    auto& ratio = registry_.ctx().get<Context>().ratio;
    /* Update frame buffer size */
    glfwGetFramebufferSize(window, &width, &height);
    ratio = static_cast<float>(width) / static_cast<float>(height);

    /* Render window */
    glfwSwapBuffers(window);

    /* Wait for events */
    glfwPollEvents();

    /* Notify window close event */
    if(glfwWindowShouldClose(window)) {
        const auto entity = registry_.create();
        registry_.emplace<WindowClose>(entity);
    }
}

bool Window::should_close() const
{
    auto& window = registry_.ctx().get<Context>().window;
    return glfwWindowShouldClose(window);
}
}
