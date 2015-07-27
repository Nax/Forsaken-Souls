#include <cstdlib>
#include <Lums>
#include "Settings.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"
#include "StateMachine.hpp"
#include "Animation.hpp"
#include "Body.hpp"
#include "BoxSet.hpp"

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
    StateMachineProvider::instance().loadBinary("bbd/machines.bbd");
    AnimationProvider::instance().loadBinary("bbd/animations.bbd");
    lm::SkeletonProvider::instance().loadBinary("bbd/skeletons.bbd");
    BodyProvider::instance().loadBinary("bbd/bodies.bbd");
    BoxProvider::instance().loadBinary("bbd/boxes.bbd");

    initUserDataIO();
    core.push<MainMenu>();
    //core.push<PauseMenu>();
    
    core.start();
}
