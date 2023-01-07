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

constexpr float PI = 3.14159265359;

namespace RenderLib
{
Transform::Transform()
    : quat_(Eigen::Quaternionf::Identity()),
      pos_(Eigen::Vector3f::Zero())
{
}

Transform::~Transform()
{
}
void Transform::set_pos(const Eigen::Vector3f& pos)
{
    pos_ = pos;
}

Eigen::Vector3f Transform::get_pos() const
{
    return pos_;
}

void Transform::set_quat(const Eigen::Quaternionf& quat)
{
    quat_ = quat;
}

Eigen::Quaternionf Transform::get_quat() const
{
    return quat_;
}

Eigen::Vector3f& Transform::pos()
{
    return pos_;
}

const Eigen::Vector3f& Transform::pos() const
{
    return pos_;
}


Eigen::Quaternionf& Transform::quat()
{
    return quat_;
}
const Eigen::Quaternionf& Transform::quat() const
{
    return quat_;
}

void Transform::from_rpy(const float& roll, const float& pitch, const float& yaw)
{
    quat_ = Eigen::AngleAxisf(roll, Eigen::Vector3f::UnitX())
            * Eigen::AngleAxisf(pitch, Eigen::Vector3f::UnitY())
            * Eigen::AngleAxisf(yaw, Eigen::Vector3f::UnitZ());
}

Eigen::Vector3f Transform::to_rpy() const
{
    auto euler = quat_.toRotationMatrix().eulerAngles(0, 1, 2);

    return euler * 180.f / PI;
}

Eigen::Matrix4f Transform::get_mat() const
{
    Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
    auto rot = quat_.toRotationMatrix();
    ret.block(0, 0, 3, 3) = rot;
    ret.block(0, 4, 3, 4) = pos_;

    return ret;
}

}
