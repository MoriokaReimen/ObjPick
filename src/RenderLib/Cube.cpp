/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/Cube.hpp"
#include <iostream>
constexpr float vertices[] = {
     0.5f,  0.5f, 0.5f,  // top right
     0.5f, -0.5f, 0.5f,  // bottom right
    -0.5f, -0.5f, 0.5f,  // bottom left
    -0.5f,  0.5f, 0.5f,  // top left 
     0.5f,  0.5f, -0.5f,  // top right
     0.5f, -0.5f, -0.5f,  // bottom right
    -0.5f, -0.5f, -0.5f,  // bottom left
    -0.5f,  0.5f, -0.5f   // top left 
};

constexpr unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,
    0, 2, 3,
    0, 4, 8,
    0, 3, 7,
    0, 4, 5,
    0, 1, 5,
    1, 2, 6,
    1, 5, 6,
    2, 3, 7,
    2, 6, 7,
    5, 6, 7,
    4, 5, 7
};  

namespace RenderLib
{

Cube::Cube()
  : vao_(0u), vbo_(0u), ebo_(0u)
{
  glGenVertexArrays(1, &vao_);  
  glBindVertexArray(vao_);

  /* create vertex buffer */
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  

  /* create element buffer */
  glGenBuffers(1, &ebo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Cube::~Cube()
{
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ebo_);
}

void Cube::render(Camera& camera, Shader& shader)
{
  shader.use_program("Cube");
  glBindVertexArray(vao_);

  /* set uniform */
  const auto proj = camera.get_proj();
  const auto view = camera.get_view();
  const auto model = this->get_mat();
  const Eigen::Matrix4f mvp = proj * view * model / 5.0;
  // std::cout << std::endl;
  // std::cout << mvp * Eigen::Vector4f::UnitZ();
  // std::cout << std::endl;
  shader.set_uniform("MVP", mvp);

  glDrawElements(GL_LINES, sizeof(indices)/sizeof(float), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  shader.use_program("None");
}
}
