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
    : IModule(registry), shader_(), camera_(), cube_(), pick_frame_()
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
    glDepthFunc(GL_LESS);
}

void Renderer::update()
{
    const auto width = registry_.ctx().get<Window::Context>().width;
    const auto height = registry_.ctx().get<Window::Context>().height;
    const auto ratio = registry_.ctx().get<Window::Context>().ratio;
    glViewport(0, 0, width, height);
    camera_.set_perspective(30.f, 1.f / ratio, 0.01f, 10000.f);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera_.look_at(Eigen::Vector3f(-5.f, -5.f, 5.f), Eigen::Vector3f::Zero(), Eigen::Vector3f::UnitZ());

    /* Render object */
    cube_.render(camera_, shader_);

    /* render pick data */
    pick_frame_.bind();
    cube_.render_pick(camera_, shader_);
    pick_frame_.unbind();

    /* fetch pick data */
    {
      const auto mouse_x = registry_.ctx().get<Window::Context>().mouse_x;
      const auto mouse_y = registry_.ctx().get<Window::Context>().mouse_y;
      const auto window_height = registry_.ctx().get<Window::Context>().height;
      const auto x = mouse_x;
      const auto y = window_height - mouse_y;
      auto pick_data = pick_frame_.read_pixel(x, y);
      registry_.ctx().get<Context>().pick_type_id = pick_data.type_id;
      registry_.ctx().get<Context>().pick_object_id = pick_data.object_id;
      registry_.ctx().get<Context>().pick_face_id = pick_data.face_id;
    }
}

}
