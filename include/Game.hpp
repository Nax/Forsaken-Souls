#include <Lums/Lums.hpp>
#include "Player.hpp"

class Game : public lm::GameState
{
public:
	Game();
	void	update();
	void	render() const;
	void	handleEvent(const lm::Event& event);
	~Game();

private:
	Player	_player;
};