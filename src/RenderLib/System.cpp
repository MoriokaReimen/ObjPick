/*
  ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
  ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
  ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
  ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
  ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
  ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
  2023/1/7
*/
#include "RenderLib/System.hpp"
#include <spdlog/spdlog.h>
#include <thread>
#include <chrono>

constexpr double TARGET_FPS_MSEC = 20.0;

namespace RenderLib
{
System::System(entt::registry& registry)
    : IModule(registry), frame_start_(std::chrono::system_clock::now()), frame_end_(std::chrono::system_clock::now())
{
    Context ctx;
    registry_.ctx().emplace<Context>(ctx);
    spdlog::info("System Module Created");
}

System::~System()
{
    spdlog::info("System Finalized");
}

void System::init()
{
    spdlog::info("System Initialized");
}

void System::update()
{
    /* Get Frame end time */
    frame_end_ = std::chrono::system_clock::now();

    /* Sleep for target FPS */
    auto wake_up_time = frame_start_ + std::chrono::duration<double, std::milli>(TARGET_FPS_MSEC);
    std::this_thread::sleep_until(wake_up_time);

    /* Gathering FPS time information */
    std::chrono::duration<double, std::milli> diff = frame_end_ - frame_start_;
    registry_.ctx().get<Context>().fps_msec = diff.count();
    registry_.ctx().get<Context>().consumption_percent = diff.count() / TARGET_FPS_MSEC;

    /* Update system time */
    registry_.ctx().get<Context>().time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    /* Mark FPS start time for next loop */
    frame_start_ = std::chrono::system_clock::now();
}
}
