#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include <Lums>

class SettingsMenu : public lm::GameState
{
public:
	SettingsMenu();
	void	load();
	void	update();
	void	handleEvent(const lm::Event& event);
	void	render();
	void	unload();
	~SettingsMenu();

private:

	void					switchRes();

	lm::Projection          _proj;
	lm::SpriteBatch         _batch;

	int						_cursor;
	int						_resCursor;
	bool					_selectReso;
	bool					_fullscreen;
};

#endif
