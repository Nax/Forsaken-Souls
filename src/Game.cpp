#include <iostream>
#include "Game.hpp"
#include "Screen.hpp"
#include "Hud.hpp"
#include "GameOver.hpp"
#include "PauseState.hpp"
#include "Player.hpp"
#include "Physics.hpp"
#include <cstdlib>

using namespace lm;

bool debugMode = false;

Game::Game()
: _gameOverTicks(0)
{
	char const*				file = "level_links.bin";
	int32_t					linkCount;
	std::ifstream			stream(lm::resourcePath() + '/' + file, std::ios::binary);

	if (!stream.good())
	{
		std::cerr << "Error opening " << file << std::endl;
		return;
	}
	stream.read(reinterpret_cast<char*>(&linkCount), sizeof(linkCount));

	Level::_totalLinks.resize(linkCount);
	for (t_array6i& lnkAr : Level::_totalLinks)
	{
		for (int& linkPart : lnkAr)
		{
			int32_t linkDWord;

			stream.read(reinterpret_cast<char*>(&linkDWord), sizeof(linkDWord));
			linkPart = static_cast<int>(linkDWord);
		}
	}
}

void
Game::load()
{
    _player = Player();
    _level.load(2);
    _camera.focus(_player, _level.map());
}

void
Game::update()
{
    for (auto e : _entities)
    {
        e->ai()(*e, _player, _level.map());
        e->update(_level.map());
    }
    _player.update(_level.map());
    _camera.update(_player, _level.map());
    for (auto e : _entities)
    {
        Phys::checkDamages(_player, *e);
        Phys::checkDamages(*e, _player);
    }
    if (_player.dead())
        _gameOverTicks++;
    if (_gameOverTicks > 500)
        Core::get().transition<GameOver>();
}

void
Game::drawBackground(lm::SpriteBatch& sb) const
{
    const Map& m = _level.map();
    lm::Vector2f parallax = -_camera.offset() * TILE_SIZE * 0.4f;
    const lm::Image& bg = ImageProvider::get().image(ImageId::Background);

    for (int i = 0; i <= ceil(m.width() * TILE_SIZE / (bg.width() / 2)); ++i)
    {
        for (int j = 0; j <= ceil(m.height() * TILE_SIZE / (bg.height() / 2)); ++j)
            sb.draw(bg, 0, Vector2f(i * bg.width() / 2.0f + parallax.x, float(SCREEN_HEIGHT) - m.height() * TILE_SIZE + j * bg.height() / 2 - parallax.y), {0.5f, 0.5f});
    }
}

void
Game::render()
{
	lm::SpriteBatch sb;
    const Map& m = _level.map();
    
	sb.begin();
    drawBackground(sb);
	m.draw(sb, _camera, 0);
    m.draw(sb, _camera, 1);
    m.draw(sb, _camera, 2);
    for (auto e : _entities)
        e->render(sb, _camera);
    _player.render(sb, _camera);
    m.draw(sb, _camera, 3);
    m.draw(sb, _camera, 4);
	sb.end();
    hud::draw(_player);
    if (_gameOverTicks > 240)
    {
        const float alpha = 0.005f * (_gameOverTicks - 240);
        glColor4f(0, 0, 0, alpha);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(SCREEN_WIDTH, 0);
        glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
        glVertex2f(0, SCREEN_HEIGHT);
        glEnd();
    }
}

void
Game::handleEvent(const Event& event)
{
    if (event.type == Event::Type::KeyDown
        || event.type == Event::Type::KeyUp)
    {
        bool down = (event.type == Event::Type::KeyDown);

        switch (event.key)
        {
            case Key::Escape:
                if (down)
                    Core::get().stop();
                break;
            case Key::R:
                reload();
                break;
            case Key::Right:
                _player.setKey(Player::Key::Right, down);
                break;
            case Key::Left:
                _player.setKey(Player::Key::Left, down);
                break;
            case Key::Down:
                _player.setKey(Player::Key::Down, down);
                break;
            case Key::Space:
                _player.setKey(Player::Key::Space, down);
                break;
            case Key::D:
                if (down)
                    debugMode = !debugMode;
                break;
            case Key::X:
                _player.die();
                break;
            case Key::A:
                _player.setKey(Player::Key::A, down);
                break;
            case Key::P:
                if (down)
                    lm::Core::get().push<PauseState>();
                break;
            default:
                break;
        }
    }
    if (event.type == Event::Type::ButtonDown
        || event.type == Event::Type::ButtonUp)
    {
        bool down = (event.type == Event::Type::ButtonDown);
        switch (event.gamepad.button)
        {
            case 1:
                _player.setKey(Player::Key::Space, down);
                break;
            case 3:
                _player.setKey(Player::Key::A, down);
                break;
            case 4:
                _player.die();
                break;
            case 9:
                Core::get().stop();
                break;
            case 10:
                if (down)
                    debugMode = !debugMode;
                break;
            case 14:
                _player.setKey(Player::Key::Left, down);
                break;
            case 15:
                _player.setKey(Player::Key::Right, down);
                break;
            default:
                break;
        }
    }
    if (event.type == lm::Event::Type::LeftStick)
    {
        if (event.gamepad.stick.x < -0.9f)
            _player.setKey(Player::Key::Left, true);
        else
            _player.setKey(Player::Key::Left, false);
        if (event.gamepad.stick.x > 0.1f)
            _player.setKey(Player::Key::Right, true);
        else
            _player.setKey(Player::Key::Right, false);
    }
}

void
Game::unload()
{

}

Game::~Game()
{

}
