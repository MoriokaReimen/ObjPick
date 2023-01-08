#ifndef PICK_FRAME_HPP
#define PICK_FRAME_HPP
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

namespace RenderLib
{

class PickFrame
{
  public:
    struct PickData
    {
      float type_id;
      float object_id;
      float face_id;
    };
  private:
    GLuint fbo_;
    GLuint texture_;
    GLuint depth_texture_;
  public:
    PickFrame();
    ~PickFrame();
    void bind();
    void unbind();
    PickData read_pixel(const int& x, const int& y);

};
}
#endif
