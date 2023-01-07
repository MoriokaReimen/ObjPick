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

namespace RenderLib
{
System::System(entt::registry& registry)
: IModule(registry)
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
}
}
