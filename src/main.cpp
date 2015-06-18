#include <cstdlib>
#include <Lums>
#include "Assets.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

int
main(int argc, char* argv[])
{
    int width = 0;
    float scale;

    if (argc > 1)
        width = std::atoi(argv[1]);
    if (!width)
        width = 1920;
    scale = float(width) / SCREEN_WIDTH;

    srand(time(nullptr));

    lm::enableModule(lm::Module::All);
    auto& core = lm::Core::instance();
    core.setWindow(new lm::Window(width, scale * SCREEN_HEIGHT, "Forsaken Souls", false));
    Assets::init();
    Assets::setScale(scale);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    core.push<PauseMenu>();
    core.start();
}
