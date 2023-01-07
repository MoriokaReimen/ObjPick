#include "RenderLib/Camera.hpp"
#include "gtest/gtest.h"
#include <iostream>

TEST(testCamera, mvp)
{
  Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
  Eigen::Vector4f vertex(1.f, 0.f, 0.f, 1.f);
  RenderLib::Camera camera;
  camera.set_perspective(60.f, 480.f / 640.f, 0.001f, 10000.f);
  camera.look_at(Eigen::Vector3f(-5.f, -5.f, -5.f), Eigen::Vector3f::Zero(), Eigen::Vector3f::UnitY());
  auto ans = (camera.get_proj() * camera.get_view() * model) * vertex;
  std::cout << ans << std::endl;
}
