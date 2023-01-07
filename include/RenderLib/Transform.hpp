#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include <Eigen/Eigen>

namespace RenderLib
{
class Transform
{
    Eigen::Quaternionf quat_;
    Eigen::Vector3f pos_;

public:
    Transform();
    virtual ~Transform();

    void set_pos(const Eigen::Vector3f& pos);
    Eigen::Vector3f get_pos() const;

    void set_quat(const Eigen::Quaternionf& quat);
    Eigen::Quaternionf get_quat() const;

    Eigen::Vector3f& pos();
    const Eigen::Vector3f& pos() const;

    Eigen::Quaternionf& quat();
    const Eigen::Quaternionf& quat() const;

    void from_rpy(const float& roll, const float& pitch, const float& yaw);
    Eigen::Vector3f to_rpy() const;
};
}
#endif
