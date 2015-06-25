#include "PauseMenu.hpp"
#include "Assets.hpp"
#include "Screen.hpp"
#include "SettingsMenu.hpp"

PauseMenu::PauseMenu()
: _cursor(0),
 _resumeAlpha(1.f),
 _settingsAlpha(0.3f)
{

}

void
PauseMenu::load()
{
	_resumeBatch.draw(lm::FontProvider::instance().get("roboto80"), "Resume",
					{SCREEN_WIDTH / 2 - 200.f / 2.f, SCREEN_HEIGHT / 2 - 500.f / 2.f, 0.f}, {1.f, 0.f, 1.f, _resumeAlpha});
	_resumeBatch.send();

	_settingsBatch.draw(lm::FontProvider::instance().get("roboto80"), "Settings",
					{SCREEN_WIDTH / 2 - 200.f / 2.f, SCREEN_HEIGHT / 2 - 300.f / 2.f, 0.f}, {1.f, 0.f, 1.f, _settingsAlpha});
	_settingsBatch.send();

	_proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void
PauseMenu::update()
{
	_resumeAlpha = (_cursor == 0) ? fmin(_resumeAlpha + 0.03f, 1.f) : fmax(0.3f, _resumeAlpha - 0.03f);
	_settingsAlpha = (_cursor == 1) ? fmin(_settingsAlpha + 0.03f, 1.f) : fmax(0.3f, _settingsAlpha - 0.03f);

	_resumeBatch.flush();
	_resumeBatch.draw(lm::FontProvider::instance().get("roboto80"), "Resume",
					{SCREEN_WIDTH / 2 - 200.f / 2.f, SCREEN_HEIGHT / 2 - 500.f / 2.f, 0.f}, {1.f, 0.f, 1.f, _resumeAlpha});
	_resumeBatch.send();

	_settingsBatch.flush();
	_settingsBatch.draw(lm::FontProvider::instance().get("roboto80"), "Settings",
					{SCREEN_WIDTH / 2 - 200.f / 2.f, SCREEN_HEIGHT / 2 - 300.f / 2.f, 0.f}, {1.f, 0.f, 1.f, _settingsAlpha});
	_settingsBatch.send();
}

void
PauseMenu::handleEvent(const lm::Event& event)
{
	if (event.type == lm::Event::Type::KeyDown)
	{
		switch (event.key)
		{
			case lm::Key::Escape:
				lm::Core::instance().stop();
				break;
			case lm::Key::Down:
				_cursor = (_cursor + 1) % 2;
				break;
			case lm::Key::Up:
				_cursor = (_cursor == 0) ? 1 : 0;
				break;
			case lm::Key::Return:
				if (_cursor == 0)
					lm::Core::instance().stop();
					// remove();
				else
					lm::Core::instance().push<SettingsMenu>();
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
PauseMenu::render()
{
	auto& shader = lm::ShaderProvider::instance().get("basic2d");
    shader.use();
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);

	_resumeBatch.render();
	_settingsBatch.render();
}

PauseMenu::~PauseMenu()
{

}
