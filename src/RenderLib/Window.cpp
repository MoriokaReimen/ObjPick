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
#include <imgui_impl_glfw.h>
#include <spdlog/spdlog.h>

static void error_callback(int error, const char* description)
{
    spdlog::error("GLFW Error {}:{}", error, description);
}

static void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
    auto const src_str = [source]() {
        switch (source) {
        case GL_DEBUG_SOURCE_API:
            return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "WINDOW SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "SHADER COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "THIRD PARTY";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER:
            return "OTHER";
        }
        return "OTHER";
    }
    ();

    auto const type_str = [type]() {
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER:
            return "MARKER";
        case GL_DEBUG_TYPE_OTHER:
            return "OTHER";
        }
        return "OTHER";
    }
    ();

    auto const severity_str = [severity]() {
        switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "NOTIFICATION";
        case GL_DEBUG_SEVERITY_LOW:
            return "LOW";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "MEDIUM";
        case GL_DEBUG_SEVERITY_HIGH:
            return "HIGH";
        }
        return "OTHER";
    }
    ();
    spdlog::info("GL:{},{},{},{},{}", src_str, type_str, severity_str, id, message);
}

static void WindowFocusCallback(GLFWwindow* window, int focused)
{
  ImGui_ImplGlfw_WindowFocusCallback(window, focused);
}

static void CursorEnterCallback(GLFWwindow* window, int entered)
{
  ImGui_ImplGlfw_CursorEnterCallback(window, entered);
}

static void CursorPosCallback(GLFWwindow* window, double x, double y)
{
  static_cast<RenderLib::Window*>(glfwGetWindowUserPointer(window))->on_mouse_move(x, y);
  ImGui_ImplGlfw_CursorPosCallback(window, x, y);
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  static_cast<RenderLib::Window*>(glfwGetWindowUserPointer(window))->on_mouse_button(button, action, mods);
  ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

 static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
  static_cast<RenderLib::Window*>(glfwGetWindowUserPointer(window))->on_mouse_wheel(xoffset, yoffset);
  ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

static void KeyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
  static_cast<RenderLib::Window*>(glfwGetWindowUserPointer(window))->on_key(keycode, scancode, action, mods);
  ImGui_ImplGlfw_KeyCallback(window, keycode, scancode, action, mods);
}

static void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
  static_cast<RenderLib::Window*>(glfwGetWindowUserPointer(window))->on_resize(width, height);
}

static void CharCallback(GLFWwindow* window, unsigned int c)
{
  ImGui_ImplGlfw_CharCallback(window, c);
}

static void MonitorCallback(GLFWmonitor* monitor, int action)
{
  ImGui_ImplGlfw_MonitorCallback(monitor, action);
}

namespace RenderLib
{
Window::Window(entt::registry& registry)
    : IModule(registry)
{
    Context ctx{nullptr, 640, 480, 480.f/640.f};
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

    /* Enable Debug output */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(message_callback, nullptr);

     /* Install call back functions */
     glfwSetWindowFocusCallback(window, WindowFocusCallback);
     glfwSetCursorEnterCallback(window, CursorEnterCallback);
     glfwSetCursorPosCallback(window, CursorPosCallback);
     glfwSetMouseButtonCallback(window, MouseButtonCallback);
     glfwSetScrollCallback(window, ScrollCallback);
     glfwSetKeyCallback(window, KeyCallback);
     glfwSetCharCallback(window, CharCallback);
     glfwSetWindowSizeCallback(window, WindowSizeCallback);
     glfwSetMonitorCallback(MonitorCallback);
     glfwSetWindowUserPointer(window, this);
}

void Window::update()
{
    auto& window = registry_.ctx().get<Context>().window;
    auto& width = registry_.ctx().get<Context>().width;
    auto& height = registry_.ctx().get<Context>().height;
    auto& ratio = registry_.ctx().get<Context>().ratio;
    /* Update frame buffer size */
    glfwGetFramebufferSize(window, &width, &height);
    ratio = static_cast<float>(height) / static_cast<float>(width);

    /* Update mouse position */
    auto& mouse_x = registry_.ctx().get<Context>().mouse_x;
    auto& mouse_y = registry_.ctx().get<Context>().mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);

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

void Window::on_resize(int width, int height)
{
}

void Window::on_key(int key, int scancode, int action, int mods)
{
}

void Window::on_mouse_button(int button, int action, int mods)
{
}

void Window::on_mouse_move(double x_pos, double y_pos)
{
}

void Window::on_mouse_wheel(double x_offset, double y_offset)
{
}

bool Window::should_close() const
{
    auto& window = registry_.ctx().get<Context>().window;
    return glfwWindowShouldClose(window);
}
}
