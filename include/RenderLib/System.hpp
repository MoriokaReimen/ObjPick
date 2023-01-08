#ifndef SYSTEM_HPP
#define SYSTEM_HPP
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
#include <chrono>
#include <entt/entt.hpp>

namespace RenderLib
{
class System :IModule
{
    std::chrono::system_clock::time_point frame_start_;
    std::chrono::system_clock::time_point frame_end_;
public:
    struct Context {
        double fps_msec;
        double consumption_percent;
        long int time_msec;
    };
public:
    System(entt::registry& registry);
    ~System() override;
    void init() override;
    void update() override;
};
}
#endif
