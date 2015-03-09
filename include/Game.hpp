#ifndef GAME_HPP
# define GAME_HPP

# include <Lums/Lums.hpp>
# include "Player.hpp"

class Game : public lm::GameState
{
public:
	Game();
	
	void update();
	void render() const;
	void unload();
	void load();
	void handleEvent(const lm::Event& event);

	 ~Game();

private:
	Player	_player;

};

#endif // ! GAME_HPP
