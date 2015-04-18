#include <algorithm>
#include "ImageProvider.hpp"

#define ARRAY_LEN(arr)		(sizeof(arr) / sizeof(*arr))

using namespace lm;

static ImageProvider provider;

static const FrameDescriptori commonBot[] = {
	#include "CommonBot.inc"
};

static const ImageDescriptor descriptors[] =
{
	ImageDescriptor("images/tileset.png").linear(false).atlas(3, 3),
	ImageDescriptor("images/common_bot.png").atlas(/*commonBot, ARRAY_LEN(commonBot)*/12, 12)
};

ImageProvider::ImageProvider()
{
	std::fill(_loaded.begin(), _loaded.end(), false);
}

Image&
ImageProvider::image(ImageId id)
{
	int i = static_cast<int>(id);

	if (_loaded[i])
		return _images[i];
	return load(id);
}

Image&
ImageProvider::load(ImageId id)
{
	int i = static_cast<int>(id);
	const ImageDescriptor& desc = descriptors[i];

	_images[i].loadDescriptor(desc);
	_loaded[i] = true;
	return _images[i];
}

ImageProvider&
ImageProvider::get()
{
	return provider;
}

ImageProvider::~ImageProvider()
{

}
