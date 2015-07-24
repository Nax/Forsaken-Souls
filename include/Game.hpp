#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <array>
#include <Lums>
#include "Level.hpp"
#include "Camera.hpp"
#include "Systems/Input.hpp"
#include "Systems/Physics.hpp"
#include "Systems/RenderSkeleton.hpp"


class Game : public lm::GameState
{
public:
    Game();
    
    void load();
    void handleEvent(const lm::Event& event);
    void update();
    void render();
    void unload();

    void setLevel(int level, int map);

    ~Game();

private:
    void            drawBackground(lm::SpriteBatch& sb) const;

    Level           _level;
    Camera          _camera;
    int             _clock;
    int             _gameOverTicks;
    int             _healTicks;

    lm::GameObject*                 _yseult;
    lm::StaticSpriteBatch           _backBatch;
    lm::StaticSpriteBatch           _frontBatch;
    lm::StaticSpriteBatch           _parallaxBatch;
    lm::Projection                  _proj;
    lm::ShaderPipeline              _pipeline;
    lm::SpriteBatch                 _textBatch;
    std::vector<lm::GameObject*>    _gameObjects;
    System::Input                   _input;
    System::Physics                 _physics;
    System::RenderSkeleton          _renderSkeleton;
};

#endif
