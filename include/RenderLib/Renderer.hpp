#ifndef RENDERER_HPP
#define RENDERER_HPP
/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/IModule.hpp"
#include "RenderLib/Camera.hpp"
#include "RenderLib/Shader.hpp"
#include "RenderLib/Cube.hpp"
#include "RenderLib/PickFrame.hpp"

namespace RenderLib
{
class Renderer : public IModule
{
private:
    Shader shader_;
    Camera camera_;
    Cube cube_;
    PickFrame pick_frame_;

public:
    struct Context {
      int pick_type_id;
      int pick_object_id;
      int pick_face_id;
    };
public:
    Renderer(entt::registry& registry);
    ~Renderer() override;
    void init() override;
    void update() override;
};
}
#endif
