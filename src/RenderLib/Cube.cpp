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
    0, 4, 7,
    0, 7, 3,
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
    /* Create and bind cube VAO */
    glCreateVertexArrays(1, &vao_);
    /* Create Vertex buffer*/
    glCreateBuffers(1, &vbo_);
    glNamedBufferStorage(vbo_, sizeof(vertices), vertices, 0);

    /* Set up position attribute in VAO */
    glVertexArrayVertexBuffer(vao_, 0, vbo_, 0, 3 * sizeof(float));
    glVertexArrayAttribFormat(vao_, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao_, 0, 0);
    glEnableVertexArrayAttrib(vao_, 0);

    /* create element buffer */
    glCreateBuffers(1, &ebo_);
    glNamedBufferStorage(ebo_, sizeof(indices), indices, 0);
    glVertexArrayElementBuffer(vao_, ebo_);

    /* Create sbo */
    glCreateBuffers(1, &sbo_);
    int temp[sizeof(vertices) / sizeof(float)] = {0};
    glNamedBufferStorage(sbo_, sizeof(GLint) * sizeof(vertices) / sizeof(float), temp, GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayVertexBuffer(vao_, 1, sbo_, 0, sizeof(GLint));
    glVertexArrayAttribFormat(vao_, 1, 0, GL_INT, GL_FALSE, 0);
    glEnableVertexArrayAttrib(vao_, 1);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    glDeleteBuffers(1, &sbo_);
}

void Cube::render(Camera& camera, Shader& shader)
{
    shader.use_program("Cube");
    glBindVertexArray(vao_);

    /* set uniform */
    const Eigen::Matrix4f proj = camera.get_proj();
    const Eigen::Matrix4f view = camera.get_view();
    const Eigen::Matrix4f model = this->get_mat();
    const Eigen::Matrix4f mvp = model * view * proj;
    shader.set_uniform("MVP", mvp);

    glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    shader.use_program("None");
}

void Cube::render_pick(Camera& camera, Shader& shader)
{
    shader.use_program("Cube-Pick");
    glBindVertexArray(vao_);

    /* set uniform */
    const Eigen::Matrix4f proj = camera.get_proj();
    const Eigen::Matrix4f view = camera.get_view();
    const Eigen::Matrix4f model = this->get_mat();
    const Eigen::Matrix4f mvp = model * view * proj;
    shader.set_uniform("MVP", mvp);

    glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    shader.use_program("None");
}

void Cube::mark_selection(const unsigned int& face_idx)
{
  const auto vert1 = indices[face_idx * 3];
  const auto vert2 = indices[face_idx * 3 + 1];
  const auto vert3 = indices[face_idx * 3 + 2];
  int mark = 1;

  glNamedBufferSubData(sbo_, sizeof(int) * vert1, sizeof(mark), &mark);
  glNamedBufferSubData(sbo_, sizeof(int) * vert2, sizeof(mark), &mark);
  glNamedBufferSubData(sbo_, sizeof(int) * vert3, sizeof(mark), &mark);
}

void Cube::unmark_selection(const unsigned int& face_idx)
{
  const auto vert1 = indices[face_idx * 3];
  const auto vert2 = indices[face_idx * 3 + 1];
  const auto vert3 = indices[face_idx * 3 + 2];
  int mark = 0;

  glNamedBufferSubData(sbo_, sizeof(int) * vert1, sizeof(mark), &mark);
  glNamedBufferSubData(sbo_, sizeof(int) * vert2, sizeof(mark), &mark);
  glNamedBufferSubData(sbo_, sizeof(int) * vert3, sizeof(mark), &mark);
}

}
