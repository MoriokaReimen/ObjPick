/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/Renderer.hpp"
#include "RenderLib/Window.hpp"
#include <spdlog/spdlog.h>
#include <glad/gl.h>

namespace RenderLib
{
Renderer::Renderer(entt::registry& registry)
    : IModule(registry), shader_(), camera_()
{
    Context ctx;
    registry_.ctx().emplace<Context>(ctx);
    spdlog::info("Renderer Module Created");
}

Renderer::~Renderer()
{
    spdlog::info("Renderer Finalized");
}

void Renderer::init()
{
    spdlog::info("Renderer Initialized");
}

void Renderer::update()
{
  const auto width = registry_.ctx().get<Window::Context>().width;
  const auto height = registry_.ctx().get<Window::Context>().height;
  const auto ratio = registry_.ctx().get<Window::Context>().ratio;
  glViewport(0, 0, width, height);
  camera_.set_perspective(30.f, ratio, 0.001f, 10000.f);
  glClear(GL_COLOR_BUFFER_BIT);


}

}
