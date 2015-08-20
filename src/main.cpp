#include <cstdlib>
#include <Lums>
#include "Settings.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

namespace
{
    int
    initUserDataIO()
    {
        int err = lm::mkAppDataDir((lm::userDataPath() + "Forsaken Souls/").c_str());
    
        if (err)
            std::cerr << "Fucked up Lums mkdir" << std::endl;
        else
        {
            // Initialize Settings
            static_cast<void>(Settings::instance());
        }
        return err;
    }
}

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
    lm::setGlobalScale(scale);

    srand(time(nullptr));

    if (initUserDataIO())
        return 1;

    lm::enableModule(lm::Module::All);
    auto& core = lm::Core::instance();
    core.setWindow(new lm::Window(width, scale * SCREEN_HEIGHT, "Forsaken Souls", false));
    lm::TextureProvider::instance().loadBinary("bbd/textures.bbd");
    lm::ShaderProvider::instance().loadBinary("bbd/shaders.bbd");
    lm::FontProvider::instance().loadBinary("bbd/fonts.bbd");
    lm::GameObjectProvider::instance().loadBinary("bbd/objects.bbd");
    lm::SkeletonProvider::instance().loadBinary("bbd/skeletons.bbd");
    lm::MusicProvider::instance().loadBinary("bbd/music.bbd");
    lm::SfxProvider::instance().loadBinary("bbd/sfx.bbd");
    initUserDataIO();
    core.push<MainMenu>();
    //core.push<PauseMenu>();
    
    core.start();
}
