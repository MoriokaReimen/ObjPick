#include "RenderLib/RenderLib.hpp"
#include <entt/entt.hpp>
#include <cstdlib>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::info("Start App");
    entt::registry registry;
    RenderLib::System system(registry);
    RenderLib::Window window(registry);
    system.init();
    window.init();

    RenderLib::Renderer renderer(registry);
    renderer.init();
    RenderLib::GUI gui(registry);
    gui.init();

    while(!window.should_close()) {
        renderer.update();
        gui.update();
        window.update();
        system.update();
    }

    return EXIT_SUCCESS;
}
