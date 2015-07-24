#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Game.hpp"
#include "Screen.hpp"
#include "Hud.hpp"
#include "GameOver.hpp"
#include "Physics.hpp"

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
    setLevel(0, 0);

    _yseult = lm::GameObjectProvider::instance().get("yseult")();
    _yseult->position.x = 7;
    _yseult->position.y = 14;
    _yseult->position.z = 2.5f;
    _gameObjects.push_back(_yseult);
    _camera.focus(*_yseult, _level.map());
    _proj.projection = lm::ortho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 100.f, -100.f);
    _pipeline.setWindow(lm::Core::instance().window());
    //_pipeline.append(lm::ShaderProvider::instance().get("light"));
    _pipeline.append(lm::ShaderProvider::instance().get("border"));
}

void
Game::update()
{
    _input.update(_gameObjects);
    _physics.update(_gameObjects);
    _camera.update(*_yseult, _level.map());
    _renderSprite.update(_gameObjects);
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
    lm::translate(_proj.view, -off.x * TILE_SIZE, -off.y * TILE_SIZE, 0);
    lm::translate(parallaxView, -off.x * TILE_SIZE * 0.4f, -off.y * TILE_SIZE * 0.4f, 0);
    auto& shader = lm::ShaderProvider::instance().get("basic2d");
    shader.use();

    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", parallaxView);
    lm::uniform(shader, "projection", _proj.projection);
    _parallaxBatch.render();
    lm::uniform(shader, "view", _proj.view);
    _backBatch.render();
    _renderSprite.render(_gameObjects);
    _frontBatch.render();

    lm::uniform(shader, "view", identity);

    _pipeline.render();

    shader.use();

    _textBatch.begin();
    _textBatch.draw(lm::FontProvider::instance().get("roboto80"), fps, {0.0, SCREEN_HEIGHT - 100.f, -10.f});
    _textBatch.end();
}

void
Game::handleEvent(const Event& event)
{
    _input.handleEvent(_gameObjects, event);
}

void
Game::unload()
{
    for (auto go : _gameObjects)
        delete go;
    _gameObjects.clear();
    _pipeline.clear();
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
    auto& parallax = lm::TextureProvider::instance().get("backgrounds");
    int xMax = std::ceil((_level.map().width() * TILE_SIZE - SCREEN_WIDTH) / float(parallax.width() / 3.0f)) * 0.4f + std::ceil(SCREEN_WIDTH / float(parallax.width() / 3.0f));
    int yMax = std::ceil((_level.map().height() * TILE_SIZE - SCREEN_HEIGHT) / float(parallax.height() / 2.0f)) * 0.4f + std::ceil(SCREEN_HEIGHT / float(parallax.height() / 2.0f));
    for (int j = 0; j < yMax; ++j)
    {
        for (int i = 0; i < xMax; ++i)
            _parallaxBatch.draw(parallax, perlin(i, j) % 5, {i * parallax.width() / 3, j * parallax.height() / 2, 10.f});
    }
    _parallaxBatch.send();
}

Game::~Game()
{

}
