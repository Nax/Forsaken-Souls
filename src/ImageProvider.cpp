#include "ImageProvider.hpp"

static const char* imageNames[] = {
    "menu_background.png",
    "menu_title.png"
};

static ImageProvider provider;

ImageProvider::ImageProvider()
{
    for (size_t i = 0; i < 256; i++)
        _images[i] = nullptr;
}

lm::Image&
ImageProvider::loadImage(ImageID id)
{
    auto i = static_cast<int>(id);

    if (_images[i] == nullptr)
    {
        _images[i] = new lm::Image();
        _images[i]->loadFile(imageNames[i]);
    }
    return *_images[i];
}

void
ImageProvider::unloadImage(ImageID id)
{
    auto i = static_cast<int>(id);

    delete _images[i];
    _images[i] = nullptr;
}

lm::Image&
ImageProvider::getImage(ImageID id)
{
    auto i = static_cast<int>(id);

    return *_images[i];
}

ImageProvider&
ImageProvider::get()
{
    return provider;
}
