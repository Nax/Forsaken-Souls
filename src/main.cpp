#include <cstdlib>
#include <Lums>
#include "Assets.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

#include "Settings.hpp"

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
    Assets::setScale(scale);
    lm::TextureProvider::instance().loadBinary("bbd/textures.bbd");
    lm::ShaderProvider::instance().loadBinary("bbd/shaders.bbd");
    lm::FontProvider::instance().loadBinary("bbd/fonts.bbd");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int err=   lm::mkAppDataDir((lm::userDataPath() + "Forsaken Souls/").c_str());
    if (err)
        std::cerr << "Fucked up Lums mkdir" << std::endl;
    Settings&       settings_sg = lm::Singleton<Settings>::instance();
    (void)settings_sg;

    core.push<MainMenu>();
    core.start();
}
