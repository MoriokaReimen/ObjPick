#ifndef WINDOW_HPP
#define WINDOW_HPP
/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/IModule.hpp"
#include <entt/entt.hpp>
struct GLFWwindow;

namespace RenderLib
{
class Window :IModule
{
public:
    struct Context {
        GLFWwindow* window;
        int width;
        int height;
        float aspect;
        double mouse_x;
        double mouse_y;
    };

    struct WindowClose {};
public:
    Window(entt::registry& registry);
    ~Window() override;
    void init() override;
    void update() override;
    bool should_close() const;

    void on_resize(int width, int height);
    void on_key(int key, int scancode, int action, int mods);
    void on_mouse_button(int button, int action, int mods);
    void on_mouse_move(double x_pos, double y_pos);
    void on_mouse_wheel(double x_offset, double y_offset);
};
}
#endif
