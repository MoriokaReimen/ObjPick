/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/PickFrame.hpp"
#include <spdlog/spdlog.h>

constexpr unsigned int WIDTH = 5000;
constexpr unsigned int HEIGHT = 5000;

namespace RenderLib
{
  PickFrame::PickFrame()
  {
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

    // Create the texture object for the primitive information buffer
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WIDTH, HEIGHT,
                0, GL_RGB, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                texture_, 0);

    // Create the texture object for the depth buffer
    glGenTextures(1, &depth_texture_);
    glBindTexture(GL_TEXTURE_2D, depth_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT,
                0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                depth_texture_, 0);


    // Restore the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  PickFrame::~PickFrame()
  {
    glDeleteFramebuffers(1, &fbo_);
    glDeleteTextures(1, &texture_);
    glDeleteTextures(1, &depth_texture_);
  }

  void PickFrame::bind()
  {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
    glEnable(GL_DEPTH_TEST); 
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void PickFrame::unbind()
  {
    // Disable reading to avoid problems with older GPUs
    glReadBuffer(GL_NONE);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    // Verify that the FBO is correct
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
      spdlog::error("FB error, status: {}", status);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  PickFrame::PickData PickFrame::read_pixel(const int& x, const int& y)
  {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    const int pixel_x = x;
    const int pixel_y = y;

    struct PixelData
    {
      float type_id;
      float object_id;
      float face_id;
    }pixel_data;

    glReadPixels(pixel_x, pixel_y, 1, 1, GL_RGB, GL_FLOAT, &pixel_data);

    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    PickData data{static_cast<unsigned int>(10000.f * pixel_data.type_id), static_cast<unsigned int>(10000.f * pixel_data.object_id), static_cast<unsigned int>(10000.f * pixel_data.face_id)};

    return data;
  }
}
