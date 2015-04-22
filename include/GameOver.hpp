#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <Lums/Lums.hpp>

class GameOver : public lm::GameState
{
public:
	GameOver();
	void	handleEvent(const lm::Event& event);
	void	update();
	void	render() const;
	~GameOver();

private:
};

#endif