#include <Lums/Lums.hpp>
#include "MainMenu.hpp"

int
main()
{
    lm::Core core(1024, 576, "Forsaken Souls");

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1024, 576, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    core.push<MainMenu>();
    core.start();
    return 0;
}