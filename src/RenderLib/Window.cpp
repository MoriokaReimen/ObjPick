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
#include <spdlog/spdlog.h>

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
  }

  void init()
  {
    spdlog::info("Window Initialized");
  }

  void update()
  {
  }
}
