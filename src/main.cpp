#include <Lums/Lums.hpp>
#include "Game.hpp"
#include "Screen.hpp"

int
main()
{
    lm::Core core(SCREEN_WIDTH, SCREEN_HEIGHT, "Forsaken Souls");

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    core.push<Game>();
    core.start();

    return 0;
}
