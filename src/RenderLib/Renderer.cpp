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
    : IModule(registry), shader_(), camera_(), cube_()
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
    glEnable(GL_DEPTH_TEST);  
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_ALWAYS); 
}

void Renderer::update()
{
  const auto width = registry_.ctx().get<Window::Context>().width;
  const auto height = registry_.ctx().get<Window::Context>().height;
  const auto ratio = registry_.ctx().get<Window::Context>().ratio;
  glViewport(0, 0, width, height);
  camera_.set_perspective(60.f, 1/ ratio, 0.01f, 10.f);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  camera_.look_at(Eigen::Vector3f(0.f, 0.f, 5.f), Eigen::Vector3f::Zero(), Eigen::Vector3f::UnitX());
  cube_.render(camera_, shader_);
}

}
