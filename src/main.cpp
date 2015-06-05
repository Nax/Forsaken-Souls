#include <cstdlib>
#include <Lums>
#include "Assets.hpp"
#include "MainMenu.hpp"

int
main()
{
    srand(time(nullptr));

    lm::enableModule(lm::Module::All);
    auto& core = lm::Core::instance();
    core.setWindow(new lm::Window(1280, 800, "Forsaken Souls", false));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Assets::init();

    core.push<MainMenu>();
    core.start();
}
