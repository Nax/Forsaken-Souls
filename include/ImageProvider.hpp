#ifndef IMAGEPROVIDER_HPP
#define IMAGEPROVIDER_HPP

#include <Lums/Lums.hpp>

enum class ImageID
{
    MenuBackground,
    MenuTitle
};

class ImageProvider
{
public:
    ImageProvider();
    lm::Image&  loadImage(ImageID id);
    void        unloadImage(ImageID id);
    lm::Image&  getImage(ImageID id);
    static ImageProvider& get();

private:
    lm::Image*  _images[256];
};

#endif