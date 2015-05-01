#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <array>
#include <Lums/Lums.hpp>
#include "Player.hpp"
#include "Level.hpp"
#include "Camera.hpp"
#include "Entity.hpp"

typedef std::vector<Entity*> EntityVector;

class Game : public lm::GameState
{
public:
    Game();
    
    void load();
    void handleEvent(const lm::Event& event);
    void update();
    void render();
    void unload();

    ~Game();

    lm::ShaderProgram   sp;

private:
    typedef std::array<int, 6>      t_array6i;

    void            drawBackground(lm::SpriteBatch& sb) const;

    Player          _player;
    Level           _level;
    Camera          _camera;
    Entity*         _medicine;
    Entity*         _boss;
    int             _clock;
    int             _gameOverTicks;
    int             _healTicks;
    EntityVector    _entities;
};

#endif
