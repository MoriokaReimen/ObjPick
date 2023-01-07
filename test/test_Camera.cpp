#include "RenderLib/Camera.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_clip_space.hpp> // glm::perspectiv
#include <glm/ext/matrix_transform.hpp> // glm::perspectiv

TEST(testCamera, perspective)
{
  RenderLib::Camera camera;
  camera.set_perspective(180.f / 4.f, 480.f / 640.f, 0.001f, 10000.f);
  auto proj = camera.get_proj();
	glm::mat4 ans = glm::perspective(glm::pi<float>() * 0.25f, 480.f / 640.f, 0.001f, 10000.f);

  EXPECT_NEAR(proj(0, 0), ans[0][0], 1E-5);
  EXPECT_NEAR(proj(0, 1), ans[0][1], 1E-5);
  EXPECT_NEAR(proj(0, 2), ans[0][2], 1E-5);
  EXPECT_NEAR(proj(0, 3), ans[0][3], 1E-5);
  EXPECT_NEAR(proj(1, 0), ans[1][0], 1E-5);
  EXPECT_NEAR(proj(1, 1), ans[1][1], 1E-5);
  EXPECT_NEAR(proj(1, 2), ans[1][2], 1E-5);
  EXPECT_NEAR(proj(1, 3), ans[1][3], 1E-5);
  EXPECT_NEAR(proj(2, 0), ans[2][0], 1E-5);
  EXPECT_NEAR(proj(2, 1), ans[2][1], 1E-5);
  EXPECT_NEAR(proj(2, 2), ans[2][2], 1E-5);
  EXPECT_NEAR(proj(2, 3), ans[2][3], 1E-5);
  EXPECT_NEAR(proj(3, 0), ans[3][0], 1E-5);
  EXPECT_NEAR(proj(3, 1), ans[3][1], 1E-5);
  EXPECT_NEAR(proj(3, 2), ans[3][2], 1E-5);
  EXPECT_NEAR(proj(3, 3), ans[3][3], 1E-5);

}

TEST(testCamera, lookat)
{
  RenderLib::Camera camera;
  camera.look_at(Eigen::Vector3f(-5.f, -5.f, -5.f), Eigen::Vector3f::Zero(), Eigen::Vector3f::UnitY());
  auto view = camera.get_view();
	glm::mat4 ans = glm::lookAt(glm::vec3(-5.f, -5.f, -5.f), glm::vec3(), glm::vec3(0.f, 1.f, 0.f));

  EXPECT_NEAR(view(0, 0), ans[0][0], 1E-5);
  EXPECT_NEAR(view(0, 1), ans[0][1], 1E-5);
  EXPECT_NEAR(view(0, 2), ans[0][2], 1E-5);
  EXPECT_NEAR(view(0, 3), ans[0][3], 1E-5);
  EXPECT_NEAR(view(1, 0), ans[1][0], 1E-5);
  EXPECT_NEAR(view(1, 1), ans[1][1], 1E-5);
  EXPECT_NEAR(view(1, 2), ans[1][2], 1E-5);
  EXPECT_NEAR(view(1, 3), ans[1][3], 1E-5);
  EXPECT_NEAR(view(2, 0), ans[2][0], 1E-5);
  EXPECT_NEAR(view(2, 1), ans[2][1], 1E-5);
  EXPECT_NEAR(view(2, 2), ans[2][2], 1E-5);
  EXPECT_NEAR(view(2, 3), ans[2][3], 1E-5);
  EXPECT_NEAR(view(3, 0), ans[3][0], 1E-5);
  EXPECT_NEAR(view(3, 1), ans[3][1], 1E-5);
  EXPECT_NEAR(view(3, 2), ans[3][2], 1E-5);
  EXPECT_NEAR(view(3, 3), ans[3][3], 1E-5);

}
