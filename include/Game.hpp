#ifndef GAME_HPP
#define GAME_HPP

#include <Lums/Lums.hpp>
#include "Player.hpp"
#include "Level.hpp"

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
    Player  _player;
    Level   _level;

};

#endif
