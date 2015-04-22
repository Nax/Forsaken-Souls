#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <array>
#include <Lums/Lums.hpp>
#include "Player.hpp"
#include "Level.hpp"
#include "Camera.hpp"

class Game : public lm::GameState
{
public:
    Game();
    
    void load();
    void handleEvent(const lm::Event& event);
    void update();
    void render() const;
    void unload();

    ~Game();

private:
	typedef std::array<int, 6>		t_array6i;

    Player  _player;
    Level   _level;
    Camera  _camera;
    int     _gameOverTicks;
};

#endif
