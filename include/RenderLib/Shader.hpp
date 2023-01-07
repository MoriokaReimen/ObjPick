#ifndef SHADER_HPP
#define SHADER_HPP
/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7 
*/
#include <unordered_map>
#include <string>
#include <glad/gl.h>
#include <Eigen/Eigen>

namespace RenderLib
{
class Shader
{
  std::unordered_map<std::string, GLuint> programs_;
  GLuint current_program_;
  GLuint compile_(const std::string& vertex_src, const std::string& fragment_src);
  public:
  Shader();
  ~Shader();
  bool use_program(const std::string& program_name);

  bool set_uniform(const std::string& name, const unsigned int& value);

  bool set_uniform(const std::string& name, const int& value);
  bool set_uniform(const std::string& name, const Eigen::Vector2i& value);
  bool set_uniform(const std::string& name, const Eigen::Vector3i& value);
  bool set_uniform(const std::string& name, const Eigen::Vector4i& value);

  bool set_uniform(const std::string& name, const float& value);
  bool set_uniform(const std::string& name, const Eigen::Vector2f& value);
  bool set_uniform(const std::string& name, const Eigen::Vector3f& value);
  bool set_uniform(const std::string& name, const Eigen::Vector4f& value);

  bool set_uniform(const std::string& name, const Eigen::Matrix2f& value);
  bool set_uniform(const std::string& name, const Eigen::Matrix3f& value);
  bool set_uniform(const std::string& name, const Eigen::Matrix4f& value);




};
}
#endif
