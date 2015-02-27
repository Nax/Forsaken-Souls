
#ifndef GAME_HPP
# define GAME_HPP

# include <Lums/Lums.hpp>

class Game : public lm::GameState
{
public:
	Game();
	
	virtual void update();
	virtual void render() const;
	virtual void unload();
	virtual void load();
	virtual void handleEvent(const lm::Event& event);

	virtual ~Game();
};

#endif // ! GAME_HPP