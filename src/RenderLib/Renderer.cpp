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
    /* set camera */
    const auto width = registry_.ctx().get<Window::Context>().width;
    const auto height = registry_.ctx().get<Window::Context>().height;
    const auto aspect = registry_.ctx().get<Window::Context>().aspect;
    camera_.set_perspective(30.f, aspect, 0.01f, 10000.f);
    camera_.look_at(Eigen::Vector3f(-5.f, -5.f, 5.f), Eigen::Vector3f::Zero(), Eigen::Vector3f::UnitZ());

    /* initialize gl render */
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Render object */
    static float last_mouse_x = 0.f;
    static float last_mouse_y = 0.f;
    const auto& mouse_x = registry_.ctx().get<Window::Context>().mouse_x;
    const auto& mouse_y = registry_.ctx().get<Window::Context>().mouse_y;
    if(registry_.ctx().get<Window::Context>().left_mouse_down)
    {
      cube_.yaw(last_mouse_x - mouse_x);
      cube_.roll(last_mouse_y - mouse_y);
    }
    last_mouse_x = mouse_x;
    last_mouse_y = mouse_y;

    cube_.render(camera_, shader_);

    /* render pick data */
    pick_frame_.bind();
    cube_.render_pick(camera_, shader_);
    pick_frame_.unbind();

    /* fetch pick data */
    if(registry_.ctx().get<Window::Context>().left_mouse_down)
    {
      const auto mouse_x = registry_.ctx().get<Window::Context>().mouse_x;
      const auto mouse_y = registry_.ctx().get<Window::Context>().mouse_y;
      const auto window_height = registry_.ctx().get<Window::Context>().height;
      const auto x = mouse_x;
      const auto y = window_height - mouse_y;
      auto pick_data = pick_frame_.read_pixel(x, y);
      if(pick_data.type_id != 0)
      {
        cube_.mark_selection(pick_data.face_id);
      }
      registry_.ctx().get<Context>().pick_type_id = pick_data.type_id;
      registry_.ctx().get<Context>().pick_object_id = pick_data.object_id;
      registry_.ctx().get<Context>().pick_face_id = pick_data.face_id;
    }

    if(registry_.ctx().get<Window::Context>().right_mouse_down)
    {
      const auto mouse_x = registry_.ctx().get<Window::Context>().mouse_x;
      const auto mouse_y = registry_.ctx().get<Window::Context>().mouse_y;
      const auto window_height = registry_.ctx().get<Window::Context>().height;
      const auto x = mouse_x;
      const auto y = window_height - mouse_y;
      auto pick_data = pick_frame_.read_pixel(x, y);
      if(pick_data.type_id != 0)
      {
        cube_.unmark_selection(pick_data.face_id);
      }
      registry_.ctx().get<Context>().pick_type_id = pick_data.type_id;
      registry_.ctx().get<Context>().pick_object_id = pick_data.object_id;
      registry_.ctx().get<Context>().pick_face_id = pick_data.face_id;
    }

}

}
