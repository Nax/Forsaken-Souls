#include <algorithm>
#include "ImageProvider.hpp"

#define ARRAY_LEN(arr)		(sizeof(arr) / sizeof(*arr))

using namespace lm;

static ImageProvider provider;

static const ImageDescriptor descriptors[] =
{
	ImageDescriptor("images/tileset.png").atlas(8, 52),
	ImageDescriptor("images/common_bot.png").atlas(12, 12),
	ImageDescriptor("images/game_over.png"),
	ImageDescriptor("images/backgrounds.png").atlas(3, 2),
	ImageDescriptor("images/new_game.png"),
	ImageDescriptor("images/quit.png"),
	ImageDescriptor("images/menu_cursor.png"),
	ImageDescriptor("images/pause.png"),
    ImageDescriptor("images/common_boss.png").atlas(12, 12),
    ImageDescriptor("images/yseult.png").atlas(7, 6),
    ImageDescriptor("images/medicine.png")
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
