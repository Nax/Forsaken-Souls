#include "GameOver.hpp"
#include "Game.hpp"
#include "Screen.hpp"

GameOver::GameOver()
{

}

void
GameOver::handleEvent(const lm::Event& event)
{
	if (event.type == lm::Event::Type::KeyDown)
	{
		if (event.key == lm::Key::Return)
			lm::Core::get().transition<Game>();
	}
}

void
GameOver::update()
{

}

void
GameOver::render() const
{
	lm::SpriteBatch sb;
	const lm::Image& go = ImageProvider::get().image(ImageId::GameOver);
	lm::Vector2f pos(SCREEN_WIDTH / 2 - go.width() / 2, SCREEN_HEIGHT / 2 - go.height() / 2);

	sb.begin();
	sb.draw(go, 0, pos);
	sb.end();

}

GameOver::~GameOver()
{

}