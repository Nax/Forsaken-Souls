#include "GameOver.hpp"
#include "Game.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"

GameOver::GameOver()
{

}

void
GameOver::handleEvent(const lm::Event& event)
{

	if (event.type == lm::Event::Type::KeyDown)
	{
		if (event.key == lm::Key::Return)
			lm::Core::get().transition<MainMenu>();
	}
	if (event.type == lm::Event::Type::ButtonDown)
    {
    	if (event.gamepad.button == 9)
    		lm::Core::get().transition<MainMenu>();
	}
}

void
GameOver::update()
{

}

void
GameOver::render()
{
	lm::SpriteBatch sb;
	const lm::Image& go = ImageProvider::get().image(ImageId::GameOver);
	lm::Vector2f pos(SCREEN_WIDTH / 2 - go.width() / 4, SCREEN_HEIGHT / 2 - go.height() / 4);

	sb.begin();
	sb.draw(go, 0, pos, {0.5f, 0.5f});
	sb.end();

}

GameOver::~GameOver()
{

}