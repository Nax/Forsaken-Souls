#include <Lums>
#include "Assets.hpp"

static float gScale;

static void
initFonts()
{
    auto& provider = lm::FontProvider::instance();

    auto& roboto20 = provider.set(Assets::Font::Roboto20);
    roboto20.setSize(80.f);
    roboto20.setPath("/Library/Fonts/AppleGothic.ttf", false);
    //roboto20.setPath("fonts/Roboto-Light.ttf");
}

void
Assets::init()
{
    initFonts();
}

void
Assets::setScale(float scale)
{
    auto& provider = lm::ImageProvider::instance();

    gScale = scale;
    // for (int i = 0; i < provider.size(); ++i)
    //     provider.set(i).setScale(scale);
}

float
Assets::scale()
{
    return gScale;
}