#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <Lums>

class GameOver : public lm::GameState
{
public:
	GameOver();
    void    load();
	void	handleEvent(const lm::Event& event);
	void	update();
	void	render();
	void    unload();
    ~GameOver();

private:
    lm::StaticSpriteBatch  _gameOverBatch;
    lm::Projection         _proj;
};

#endif