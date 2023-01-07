/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7 
*/
#include "RenderLib/Shader.hpp"
#include <spdlog/spdlog.h>

namespace RenderLib
{

GLuint Shader::compile_(const std::string& vertex_src, const std::string& fragment_src)
{
  GLuint program;
  return program;
}

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::use_program(const std::string& program_name)
{
  bool ret = false;
  if(programs_.find(program_name) != programs_.end())
  {
    const GLuint program = programs_[program_name];
    glUseProgram(program);
    ret = true;
  } else {
    spdlog::error("Program {} not found", program_name);
  }

  return ret;
}
}
