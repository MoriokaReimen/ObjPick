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

static void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}
	}();
  spdlog::info("GL:{},{},{},{},{}", src_str, type_str, severity_str, id, message);
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
