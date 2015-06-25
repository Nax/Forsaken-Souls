#include "GameOver.hpp"
#include "Game.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "Assets.hpp"

GameOver::GameOver()
{

}

void
GameOver::load()
{
	auto& gameOver = lm::TextureProvider::instance().get("game_over");

	_gameOverBatch.draw(gameOver, 0, {SCREEN_WIDTH / 2 - gameOver.width() / 2, SCREEN_HEIGHT / 2 - gameOver.height() / 2, 0.f});
	_gameOverBatch.send();

	_proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void
GameOver::handleEvent(const lm::Event& event)
{

	if (event.type == lm::Event::Type::KeyDown)
	{
		if (event.key == lm::Key::Return)
			lm::Core::instance().transition<MainMenu>();
	}
	if (event.type == lm::Event::Type::ButtonDown)
    {
    	if (event.gamepad.button == 9)
    		lm::Core::instance().transition<MainMenu>();
	}
}

void
GameOver::update()
{

}

void
GameOver::render()
{
	auto& shader = lm::ShaderProvider::instance().get("basic2d");
    shader.use();
 
    _proj.view = lm::Matrix4f::identity();
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);
 
    _gameOverBatch.render();
}

void
GameOver::unload()
{

}

GameOver::~GameOver()
{

}