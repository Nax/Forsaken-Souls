#include <Lums>
#include "Assets.hpp"

static float gScale;

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