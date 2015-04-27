#include "PauseState.hpp"

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
}

bool
PauseState::forwardRender() const
{
	return true;
}

PauseState::~PauseState()
{

}
