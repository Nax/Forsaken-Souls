#ifndef ASSETS_HPP
#define ASSETS_HPP

namespace	Assets
{
	enum Image
	{
		Tileset,
		CommonBot,
		GameOver,
		Background,
		NewGame,
		Quit,
		MenuCursor,
		Pause,
		CommonBoss,
		Yseult,
		Medicine,
        Count,
	};

	using Texture = Image;

	enum Shader
	{
		Basic2D,
		Border,
		Light
	};

	enum Font
	{
		Roboto20
	};

	void	init();
    void    setScale(float scale);
    float   scale();
}

#endif