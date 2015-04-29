#include "PauseState.hpp"
#include "ImageProvider.hpp"
#include "Screen.hpp"

PauseState::PauseState()
{

}

void
PauseState::update()
{

}

void
PauseState::handleEvent(const lm::Event& event)
{
	if (event.type == lm::Event::Type::KeyDown)
	{
		switch (event.key)
		{
			case lm::Key::P:
			case lm::Key::Escape:
				remove();
				break;
			default:
				break;
		}
	}
	if (event.type == lm::Event::Type::ButtonDown)
	{
		if (event.gamepad.button == 9)
			remove();
	}
}

void
PauseState::render()
{
	glColor4f(0, 0, 0, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(1920, 0);
	glVertex2f(1920, 1080);
	glVertex2f(0, 1080);
	glEnd();
	glColor4f(1, 1, 1, 1);
	lm::SpriteBatch sb;
    const lm::Image& pause = ImageProvider::get().image(ImageId::Pause);
    sb.begin();
    sb.draw(pause, 0, {SCREEN_WIDTH / 2 - pause.width() * 0.5f / 2, SCREEN_HEIGHT / 2 - pause.height() * 0.5f / 2}, {0.5f, 0.5f});
    sb.end();
}

bool
PauseState::forwardRender() const
{
	return true;
}

bool
PauseState::forwardEvent(const lm::Event& event) const
{
    return true;
}

PauseState::~PauseState()
{

}
