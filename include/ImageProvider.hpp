#ifndef IMAGE_PROVIDER_HPP
#define IMAGE_PROVIDER_HPP

#include <array>
#include <Lums/Lums.hpp>

enum class ImageId
{
	Tileset,
	CommonBot,
	GameOver,
	Background,
	NewGame,
	Quit,
	MenuCursor,
	Pause
};

class ImageProvider
{
public:
	ImageProvider();
	lm::Image&				image(ImageId id);
	lm::Image&				load(ImageId id);
	static ImageProvider& 	get();
	~ImageProvider();

private:
	std::array<lm::Image, 256>	_images;
	std::array<bool, 256>		_loaded;
};

#endif
