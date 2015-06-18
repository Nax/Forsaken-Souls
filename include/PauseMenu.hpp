#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <Lums>

class PauseMenu : public lm::GameState
{
public:
	PauseMenu();
	void	load();
	void	update();
	void	handleEvent(const lm::Event& event);
	void	render();
	~PauseMenu();

private:
	lm::Projection          _proj;
	lm::SpriteBatch         _resumeBatch;
	lm::SpriteBatch         _settingsBatch;
	int						_cursor;
	float					_resumeAlpha;
	float					_settingsAlpha;
};

#endif
