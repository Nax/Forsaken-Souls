#include <Lums/Lums.hpp>
#include "MainMenu.hpp"
#include "Screen.hpp"
#include <cstdlib>

int
main()
{
    lm::Core core(SCREEN_WIDTH, SCREEN_HEIGHT, "Forsaken Souls");
    // lm::ShaderProgram sp;


    // srand(time(nullptr));
    // sp.attach(lm::Shader("shaders/lightFrag.glsl", lm::Shader::Type::Fragment));
    // sp.attach(lm::Shader("shaders/lightVert.glsl", lm::Shader::Type::Vertex));
    // sp.attach(lm::Shader::fragment());
    // sp.attach(lm::Shader::vertex());
    // sp.link();
    // sp.use();

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    core.push<MainMenu>();
    core.window().resize(2560 / 2, 1600 / 2, true);
    // core.window().resize(2560, 1440, true);
    core.start();

    return 0;
}
