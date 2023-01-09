#ifndef CUBE_HPP
#define CUBE_HPP
/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include <glad/gl.h>
#include "RenderLib/Transform.hpp"
#include "RenderLib/IRenderObject.hpp"

namespace RenderLib
{
class Cube : public Transform, IRenderObject
{
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
    GLuint sbo_;
public:
    Cube();
    ~Cube() override;
    void render(Camera& camera, Shader& shader) override;
    void render_pick(Camera& camera, Shader& shader);
    void mark_selection(const unsigned int& face_idx);
    void unmark_selection(const unsigned int& face_idx);
};

}
#endif
