#ifndef CAMERA_HPP
#define CAMERA_HPP
/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/Transform.hpp"
#include <Eigen/Eigen>

namespace RenderLib
{

  class Camera : public Transform
  {
    Eigen::Matrix4f proj_;
    public:
    Camera();
    ~Camera() override;
    Eigen::Matrix4f get_view() const;
    Eigen::Matrix4f get_proj() const;

    void set_perspective(const float& fovy, const float& aspect, const float& zNear, const float& zFar);
    void set_ortho(const float& left, const float& right, const float& bottom,
                   const float& top,  const float& zNear, const float& zFar);
    void look_at(const Eigen::Vector3f& eye, const Eigen::Vector3f& center, const Eigen::Vector3f& up);
  };

}
#endif
