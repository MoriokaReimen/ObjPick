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
#include <cmrc/cmrc.hpp>
CMRC_DECLARE(shaders);

namespace RenderLib
{

GLuint Shader::compile_(const std::string& vertex_path, const std::string& fragment_path)
{
  GLuint program = glCreateProgram();
  auto fs = cmrc::shaders::get_filesystem();

  /* Compile vertex shader */
  const auto vertex_data = fs.open(vertex_path);
  const std::string vertex_code(vertex_data.cbegin(), vertex_data.cend());
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  const char* vertex_p = vertex_code.data(); 
  glShaderSource(vertex_shader, 1, &vertex_p, NULL);
  glCompileShader(vertex_shader);

	/* Check Vertex Shader */
  {
    GLint result = GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
    if(result)
    {
      spdlog::info("{} : OK", vertex_path);
    }

    int message_length;
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &message_length);
    if ( message_length > 0 ){
      std::string message;
      message.resize(message_length+1);
      glGetShaderInfoLog(vertex_shader, message_length, NULL, &message[0]);
      spdlog::info("{} : {}", vertex_path, message);
    }
  }

  /* Compile fragment shader */
  const auto fragment_data = fs.open(fragment_path);
  const std::string fragment_code(fragment_data.cbegin(), fragment_data.cend());
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragment_p = fragment_code.data();
  glShaderSource(fragment_shader, 1, &fragment_p, NULL);
  glCompileShader(fragment_shader);

	/* Check Fragment Shader */
  {
    GLint result = GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
    if(result)
    {
      spdlog::info("{} : OK", fragment_path);
    }

    int message_length;
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &message_length);
    if ( message_length > 0 ){
      std::string message;
      message.resize(message_length+1);
      glGetShaderInfoLog(fragment_shader, message_length, NULL, &message[0]);
      spdlog::info("{} : {}", fragment_path, message);
    }
  }

  /* Link program */
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

	/* Check the program */
  {
    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(result)
    {
      spdlog::info("Link {} {}: OK", vertex_path, fragment_path);
    }

    int message_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &message_length);
    if ( message_length > 0 ){
      std::string message;
      message.resize(message_length+1);
      glGetProgramInfoLog(program, message_length, NULL, &message[0]);
      spdlog::info("Link {} {} : {}", vertex_path, fragment_path, message);
    }
  }
  /* Cleanup shaders */
	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

  return program;
}

Shader::Shader()
{
  /* Compile cube shader */
  {
    auto program = compile_("shader/Cube.vert", "shader/Cube.frag");
    programs_["Cube"] = program;
  }
}

Shader::~Shader()
{
  for(const auto& elem : programs_)
  {
    spdlog::info("Delete Shader : {}", elem.first);
    glDeleteProgram(elem.second);
  }
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
