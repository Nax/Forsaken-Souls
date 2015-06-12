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
#include <chrono>

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
    //_level.map().enlight(sp, _camera);
    // for (auto e : _entities)
    //{
    //    if (e->id() == 3)
    //        _medicine = e;
    //    if (e->id() == 2)
    //        _boss = e;
    // }
    setLevel(2, 0);
    _level.map().spawn(_entities);
    _camera.focus(_player, _level.map());
    _proj.projection = lm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    _pipeline.setWindow(lm::Core::instance().window());
    //_pipeline.append(lm::ShaderProvider::instance().get(Assets::Shader::Light));
    _pipeline.append(lm::ShaderProvider::instance().get(Assets::Shader::Border));
}

void
Game::update()
{
    // _clock = (_clock + 1) % 1000;
    // int loc = glGetUniformLocation(sp.program(), "clock");
    // glUniform1i(loc, _clock);

    for (auto e : _entities)
    {
        if (e->ai())
            e->ai()(*e, _player, _level.map());
        e->update(_level.map());
    }
    _player.update(_level.map());
    _camera.update(_player, _level.map());
    //_level.map().enlight(sp, _camera);

    for (auto e : _entities)
    {
        Phys::checkDamages(_player, *e);
        Phys::checkDamages(*e, _player);
    }
    if (_player.dead())
        _gameOverTicks++;
    if (_gameOverTicks > 500)
        Core::instance().transition<GameOver>();
}

void
Game::render()
{
    static double fpsc = 0;
    static double fpssum = 0;
    static int fpscount = 0;
    char fps[256];
    static auto t0 = std::chrono::high_resolution_clock::now();
    auto t1 = std::chrono::high_resolution_clock::now();
    fpssum += 1000000000.0 / std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count();
    fpscount += 1;
    if (fpscount == 15)
    {
        fpscount = 0;
        fpsc = fpssum / 15.0;
        fpssum = 0;
    }
    t0 = t1;
    snprintf(fps, 256, "%5.0lf FPS", fpsc);

    lm::Vector2f off = _camera.offset();
    Matrix4f parallaxView = lm::Matrix4f::identity();
    Matrix4f identity = lm::Matrix4f::identity();

    _pipeline.bind();
    
    _proj.view = identity;
    lm::translate(_proj.view, -off.x * TILE_SIZE, off.y * TILE_SIZE, 0);
    lm::translate(parallaxView, -off.x * TILE_SIZE * 0.4f, off.y * TILE_SIZE * 0.4f, 0);
    auto& shader = lm::ShaderProvider::instance().get(Assets::Shader::Basic2D);
    shader.use();

    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", parallaxView);
    lm::uniform(shader, "projection", _proj.projection);
    _parallaxBatch.render();
    lm::uniform(shader, "view", _proj.view);
    _backBatch.render();
    _entitiesBatch.begin();
    for (auto e : _entities)
        e->render(_entitiesBatch, _camera);
    _player.render(_entitiesBatch, _camera);
    _entitiesBatch.end();
    _frontBatch.render();

    lm::uniform(shader, "view", identity);

    _pipeline.render();

    shader.use();

    _textBatch.begin();
    _textBatch.draw(lm::FontProvider::instance().get(Assets::Font::Roboto20), fps);
    _textBatch.end();
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

static int
perlin(int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return nn;
}

void
Game::setLevel(int level, int map)
{
    _level.load(level);
    _level.setCurrent(map);
    _backBatch.flush();
    _level.map().drawBack(_backBatch);
    _backBatch.send();
    _frontBatch.flush();
    _level.map().drawFront(_frontBatch);
    _frontBatch.send();
    _parallaxBatch.flush();
    auto& parallax = lm::TextureProvider::instance().get(Assets::Texture::Background);
    int xMax = std::ceil((_level.map().width() * TILE_SIZE - SCREEN_WIDTH) / float(parallax.width() / 3.0f)) * 0.4f + std::ceil(SCREEN_WIDTH / float(parallax.width() / 3.0f));
    int yMax = std::ceil((_level.map().height() * TILE_SIZE - SCREEN_HEIGHT) / float(parallax.height() / 2.0f)) * 0.4f + std::ceil(SCREEN_HEIGHT / float(parallax.height() / 2.0f));
    for (int j = 0; j < yMax; ++j)
    {
        for (int i = 0; i < xMax; ++i)
            _parallaxBatch.draw(parallax, perlin(i, j) % 5, {i * parallax.width() / 3, SCREEN_HEIGHT - (j + 1) * parallax.height() / 2});
    }
    _parallaxBatch.send();
}

Game::~Game()
{

}
