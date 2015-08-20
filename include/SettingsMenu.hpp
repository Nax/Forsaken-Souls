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

	void					apply();

	lm::Projection          	_proj;
	lm::SpriteBatch         	_batch;
	std::vector<lm::Vector2i>	_resolutions;

	int						_cursor;
	int						_resCursor;
	bool					_fullscreen;

};

#endif
