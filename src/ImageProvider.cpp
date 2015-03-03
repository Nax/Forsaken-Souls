#include <algorithm>
#include "ImageProvider.hpp"

using namespace lm;

static ImageProvider provider;

static const FrameDescriptori alucard[] = {
	#include "Alucard.inc"
};

static const ImageDescriptor descriptors[] =
{
	ImageDescriptor("images/alucard.png").linear(false).atlas(alucard, sizeof(alucard) / sizeof(*alucard))
};

ImageProvider::ImageProvider()
{
	std::fill(_images.begin(), _images.end(), false);
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