#include <cstdlib>
#include <Lums>
#include "Settings.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"
#include "Language.hpp"

static void
loadSettings()
{
    auto& settings = Settings::instance();
    int width;
    int height;
    bool fullscreen;
    Language lang;

    const std::string& res = settings.get("resolution");
    int sep = res.find('x') + 1;
    width = atoi(res.c_str());
    height = atoi(res.c_str() + sep);
    lang = (settings.get("lang") == "fr" ? Language::French : Language::English);
    fullscreen = (settings.get("fullscreen") == "0" ? false : true);
    lm::Core::instance().window().resize(width, height, fullscreen);
    lm::setGlobalScale(float(height) / SCREEN_HEIGHT);
    LanguageManager::instance().set(lang);
}

int
main()
{
    srand(time(nullptr));

    lm::enableModule(lm::Module::All);
    auto& core = lm::Core::instance();
    core.setWindow(new lm::Window(1280, 800, "Forsaken Souls", false));
    lm::TextureProvider::instance().loadBinary("bbd/textures.bbd");
    lm::ShaderProvider::instance().loadBinary("bbd/shaders.bbd");
    lm::FontProvider::instance().loadBinary("bbd/fonts.bbd");
    lm::GameObjectProvider::instance().loadBinary("bbd/objects.bbd");
    lm::SkeletonProvider::instance().loadBinary("bbd/skeletons.bbd");
    lm::MusicProvider::instance().loadBinary("bbd/music.bbd");
    lm::SfxProvider::instance().loadBinary("bbd/sfx.bbd");
    loadSettings();
    core.push<MainMenu>();
    //core.push<PauseMenu>();
    
    core.start();
}
