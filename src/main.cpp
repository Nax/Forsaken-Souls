#include <Lums/Lums.hpp>
#include "Game.hpp"

int
main()
{
    lm::Core core(1024, 768, "Forsaken Souls");

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1024, 768, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    core.push<Game>();
    core.start();

    return 0;
}
