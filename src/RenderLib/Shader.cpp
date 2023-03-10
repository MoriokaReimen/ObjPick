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

        int message_length;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &message_length);
        if ( message_length > 0 ) {
            std::string message;
            message.resize(message_length+1);
            glGetShaderInfoLog(vertex_shader, message_length, NULL, &message[0]);
            spdlog::info("{} : {}", vertex_path, message);
        }

        if(result) {
            spdlog::info("{} : OK", vertex_path);
        } else {
            spdlog::info("{} : NG", vertex_path);
            throw std::runtime_error("Vertex compile fail");
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

        int message_length;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &message_length);
        if ( message_length > 0 ) {
            std::string message;
            message.resize(message_length+1);
            glGetShaderInfoLog(fragment_shader, message_length, NULL, &message[0]);
            spdlog::info("{} : {}", fragment_path, message);
        }
        if(result) {
            spdlog::info("{} : OK", fragment_path);
        } else {
            spdlog::error("{} : NG", fragment_path);
            throw std::runtime_error("Fragment compile fail");
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

        int message_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &message_length);
        if ( message_length > 0 ) {
            std::string message;
            message.resize(message_length+1);
            glGetProgramInfoLog(program, message_length, NULL, &message[0]);
            spdlog::info("Link {} {} : {}", vertex_path, fragment_path, message);
        }
        if(result) {
            spdlog::info("Link {} {}: OK", vertex_path, fragment_path);
        } else {
            spdlog::error("Link {} {}: NG", vertex_path, fragment_path);
            throw std::runtime_error("Link fail");
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
    : programs_(), current_program_(0u)
{
    /* Compile None shader */
    programs_["None"] = 0u;

    /* Compile cube shader */
    {
        auto program = compile_("shader/Cube.vert", "shader/Cube.frag");
        programs_["Cube"] = program;
    }

    /* Compile cube shader */
    {
        auto program = compile_("shader/Cube-Pick.vert", "shader/Cube-Pick.frag");
        programs_["Cube-Pick"] = program;
    }

    introspect();
}

Shader::~Shader()
{
    for(const auto& elem : programs_) {
        spdlog::info("Delete Shader : {}", elem.first);
        glDeleteProgram(elem.second);
    }
}

bool Shader::use_program(const std::string& program_name)
{
    bool ret = false;
    if(programs_.find(program_name) != programs_.end()) {
        const GLuint program = programs_[program_name];
        glUseProgram(program);
        current_program_ = program;
        ret = true;
    } else {
        spdlog::error("Program {} not found", program_name);
    }

    return ret;
}

bool Shader::set_uniform(const std::string& name, const unsigned int& value)
{
    bool ret = true;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform1ui(current_program_, location, value);

    return ret;
}

bool Shader::set_uniform(const std::string& name, const int& value)
{
    bool ret = true;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform1i(current_program_, location, value);

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Vector2i& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform2iv(current_program_, location, 1, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Vector3i& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform3iv(current_program_, location, 1, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Vector4i& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform4iv(current_program_, location, 1, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const float& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform1i(current_program_, location, value);
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Vector2f& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform2fv(current_program_, location, 1, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Vector3f& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform3fv(current_program_, location, 1, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Vector4f& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniform4fv(current_program_, location, 1, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Matrix2f& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniformMatrix2fv(current_program_, location, 1, GL_TRUE, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Matrix3f& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniformMatrix3fv(current_program_, location, 1, GL_TRUE, value.data());
    ret = true;

    return ret;
}

bool Shader::set_uniform(const std::string& name, const Eigen::Matrix4f& value)
{
    bool ret = false;
    const GLuint location = glGetUniformLocation(current_program_, name.c_str());
    glProgramUniformMatrix4fv(current_program_, location, 1, GL_TRUE, value.data());
    ret = true;

    return ret;
}

void Shader::introspect() const
{
    const int max_name_length = 64;
    const int num_parameters = 2;
    GLint num_outputs = 0;
    for(const auto& elem : programs_) {
        if(elem.first == "None") continue;
        spdlog::info("Program {} introspect:", elem.first);

        /* Get Program Output */
        glGetProgramInterfaceiv(elem.second, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &num_outputs);
        static const GLenum properties[] { GL_TYPE, GL_LOCATION };
        GLint params[num_parameters];
        GLchar name[max_name_length];
        for (GLuint index = 0; index != num_outputs; ++index) {
            glGetProgramResourceName(elem.second, GL_PROGRAM_OUTPUT, index, sizeof(name), nullptr, name);
            glGetProgramResourceiv(elem.second, GL_PROGRAM_OUTPUT, index, num_parameters, properties, num_parameters, nullptr, params);
            spdlog::info("Index: {} is type {} is named {} at location {}", index, params[0], name, params[1]);
        }

        /* Get Uniform information */
        GLint numBlocks = 0;
        glGetProgramInterfaceiv(elem.second, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numBlocks);
        const GLenum blockProperties[1] = {GL_NUM_ACTIVE_VARIABLES};
        const GLenum activeUnifProp[1] = {GL_ACTIVE_VARIABLES};
        const GLenum unifProperties[3] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

        for(GLuint i = 0; i < numBlocks; ++i) {
            GLsizei length;
            GLint size;
            GLenum type;
            std::string name;
            name.resize(256);
            glGetActiveUniform(elem.second, i, 256, &length, &size, &type, &name[0]);
            spdlog::info("Uniform {} is type {} at {}", name, type, i);
        }
    }
}
}
