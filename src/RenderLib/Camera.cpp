/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include <RenderLib/Camera.hpp>

namespace RenderLib
{
Camera::Camera()
    : Transform()
{
}

Camera::~Camera()
{
}

Eigen::Matrix4f Camera::get_view() const
{
    Eigen::Matrix3f mat3 = quat().toRotationMatrix();
    Eigen::Matrix4f mat4 = Eigen::Matrix4f::Identity();
    mat4.block(0, 0, 3, 3) = mat3;
    mat4.block(0, 4, 3, 4) = pos();

    return mat4;
}

Eigen::Matrix4f Camera::get_proj() const
{
    return proj_;
}

void Camera::set_perspective(const float& fovy, const float& aspect, const float& zNear, const float& zFar)
{
    Eigen::Transform<float,3, Eigen::Projective> tr;
    tr.matrix().setZero();
    assert(aspect > 0);
    assert(zFar > zNear);
    assert(zNear > 0);
    float radf = M_PI * fovy / 180.0;
    float tan_half_fovy = std::tan(radf / 2.0);
    tr(0,0) = 1.0 / (aspect * tan_half_fovy);
    tr(1,1) = 1.0 / (tan_half_fovy);
    tr(2,2) = - (zFar + zNear) / (zFar - zNear);
    tr(3,2) = - 1.0;
    tr(2,3) = - (2.0 * zFar * zNear) / (zFar - zNear);
    proj_ =  tr.matrix();

}

void Camera::set_ortho(const float& left, const float& right, const float& bottom,
                       const float& top,  const float& zNear, const float& zFar)
{
    Eigen::Matrix4f mat = Eigen::Matrix4f::Identity();
    mat(0,0) = 2.f / (right - left);
    mat(1,1) = 2.f / (top - bottom);
    mat(2,2) = - 2.f / (zFar - zNear);
    mat(3,0) = - (right + left) / (right - left);
    mat(3,1) = - (top + bottom) / (top - bottom);
    mat(3,2) = - (zFar + zNear) / (zFar - zNear);

    proj_ = mat;
}

void Camera::look_at(const Eigen::Vector3f& eye, const Eigen::Vector3f& center, const Eigen::Vector3f& up)
{
    Eigen::Vector3f f = (center - eye).normalized();
    Eigen::Vector3f u = up.normalized();
    Eigen::Vector3f s = f.cross(u).normalized();
    u = s.cross(f);
    Eigen::Matrix3f mat = Eigen::Matrix3f::Zero();
    mat(0,0) = s.x();
    mat(0,1) = s.y();
    mat(0,2) = s.z();
    mat(1,0) = u.x();
    mat(1,1) = u.y();
    mat(1,2) = u.z();
    mat(2,0) = -f.x();
    mat(2,1) = -f.y();
    mat(2,2) = -f.z();

    quat() = Eigen::Quaternionf(mat);
    pos() = Eigen::Vector3f(-s.dot(eye), -u.dot(eye), f.dot(eye));
}

}
