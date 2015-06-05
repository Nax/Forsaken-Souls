#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <Lums>

class PauseState : public lm::GameState
{
public:
	PauseState();
	void	update();
	void	handleEvent(const lm::Event& event);
	void	render();
	bool	forwardRender() const;
    bool    forwardEvent(const lm::Event& event) const;
	~PauseState();
};

#endif
