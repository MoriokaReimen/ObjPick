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

constexpr unsigned int WIDTH = 1000;
constexpr unsigned int HEIGHT = 1000;

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

    // Disable reading to avoid problems with older GPUs
    glReadBuffer(GL_NONE);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    // Verify that the FBO is correct
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
      spdlog::error("FB error, status: {}", status);
    }

    // Restore the default framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
  }

  void PickFrame::unbind()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  PickFrame::PickData PickFrame::read_pixel(const float& x, const float& y)
  {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    const unsigned int pixel_x = x * WIDTH;
    const unsigned int pixel_y = y * HEIGHT;

    PickData pick;
    glReadPixels(pixel_x, pixel_y, 1, 1, GL_RGB, GL_FLOAT, &pick);

    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    return pick;
  }
}
