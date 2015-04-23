#include <Lums/Lums.hpp>
#include "Game.hpp"
#include "Screen.hpp"
#include <cstdlib>

int
main()
{
    lm::Core core(SCREEN_WIDTH, SCREEN_HEIGHT, "Forsaken Souls");
    // lm::ShaderProgram sp;

    // sp.attach(lm::Shader("shaders/frag.glsl", lm::Shader::Type::Fragment));
    // sp.attach(lm::Shader("shaders/vert.glsl", lm::Shader::Type::Vertex));
    // sp.attach(lm::Shader::fragment());
    // sp.attach(lm::Shader::vertex());
    // sp.link();
    // sp.use();

    srand(time(nullptr));

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    core.push<Game>();
    core.window().resize(2560, 1440, true);
    //core.window().resize(3840, 2160, true);
    core.start();

    return 0;
}
