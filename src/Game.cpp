#include <iostream>
#include "Game.hpp"
#include "Screen.hpp"
#include "Hud.hpp"
#include "GameOver.hpp"
#include "PauseState.hpp"
#include "Player.hpp"
#include "Physics.hpp"
#include "Assets.hpp"
#include <cstdlib>

using namespace lm;

bool debugMode = false;

Game::Game()
{
}

void
Game::load()
{
    _clock = 0;
    _gameOverTicks = 0;
    _healTicks = 0;
    _player = Player();
    //_camera.focus(_player, _level.map());
    //_level.map().spawn(_entities);
    //_level.map().enlight(sp, _camera);
   // for (auto e : _entities)
    //{
    //    if (e->id() == 3)
    //        _medicine = e;
    //    if (e->id() == 2)
    //        _boss = e;
   // }
    setLevel(2, 0);
    _proj.projection = lm::ortho(0, 1920, 1080, 0);
}

void
Game::update()
{
    // _clock = (_clock + 1) % 1000;
    // int loc = glGetUniformLocation(sp.program(), "clock");
    // glUniform1i(loc, _clock);

    // for (auto e : _entities)
    // {
    //     if (e->ai())
    //         e->ai()(*e, _player, _level.map());
    //     e->update(_level.map());
    // }
    // _player.update(_level.map());
    // _camera.update(_player, _level.map());
    // _level.map().enlight(sp, _camera);

    // if (_medicine)
    // {
    //     if (Phys::checkDamages(*_medicine, _player))
    //     {
    //         _player.heal(50);
    //         _entities.erase(std::find(_entities.begin(), _entities.end(), _medicine));
    //         delete _medicine;
    //         _medicine = nullptr;
    //     }
    // }
    // for (auto e : _entities)
    // {
    //     Phys::checkDamages(_player, *e);
    //     Phys::checkDamages(*e, _player);
    // }
    // if (_player.dead() || _boss->dead())
    //     _gameOverTicks++;
    // if (_gameOverTicks > 500)
    //     Core::instance().transition<GameOver>();
}

static int
perlin(int x,int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return nn;
}

void
Game::drawBackground(lm::SpriteBatch& sb) const
{
    // const Map& m = _level.map();
    // lm::Vector2f parallax = -_camera.offset() * TILE_SIZE * 0.4f;
    // const lm::Image& bg = ImageProvider::get().image(ImageId::Background);
    // const lm::Vector2f bgDim = { bg.width() / 3.f, bg.height() / 2.f };

    // for (int i = 0; i <= ceil(m.width() * TILE_SIZE / (bgDim.x / 2.f)); ++i)
    // {
    //     for (int j = 0; j <= ceil(m.height() * TILE_SIZE / (bgDim.y / 2.f)); ++j)
    //         sb.draw(bg, perlin(i, j) % 5, Vector2f(i * bgDim.x / 2.0f + parallax.x, float(SCREEN_HEIGHT) - m.height() * TILE_SIZE + j * bgDim.y / 2.f - parallax.y), {0.5f, 0.5f});
    // }
}

void
Game::render()
{
    auto& shader = lm::ShaderProvider::instance().get(Assets::Shader::Basic2D);
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);
    _backBatch.render();
    _frontBatch.render();
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
                    Core::instance().stop();
                break;
            case Key::R:
                if (down)
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
                    lm::Core::instance().push<PauseState>();
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
                if (down)
                    lm::Core::instance().push<PauseState>();
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
    for (auto e : _entities)
        delete e;
    _entities.clear();
}

void
Game::setLevel(int level, int map)
{
    _level.load(map);
    _backBatch.flush();
    _level.map().drawBack(_backBatch);
    _backBatch.send();
    _frontBatch.flush();
    _level.map().drawFront(_frontBatch);
    _frontBatch.send();
}

Game::~Game()
{

}
