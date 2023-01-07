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
        float ratio;
    };

    struct WindowClose {};
public:
    Window(entt::registry& registry);
    ~Window() override;
    void init() override;
    void update() override;
    bool should_close() const;
};
}
#endif
