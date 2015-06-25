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
	~SettingsMenu();

private:
	lm::Projection          _proj;
	lm::SpriteBatch         _resumeBatch;
	lm::SpriteBatch         _keyBatch;
	lm::SpriteBatch         _resolutionBatch;
	lm::SpriteBatch         _res1Batch;
	lm::SpriteBatch         _res2Batch;
	lm::SpriteBatch         _res3Batch;
	lm::SpriteBatch         _fullscreenBatch;
	float					_resumeAlpha;
	float					_keyAlpha;
	float					_resoAlpha;
	float					_res1Alpha;
	float					_res2Alpha;
	float					_res3Alpha;
	float					_fullscreenAlpha;

	int						_cursor;
	int						_resCursor;
	bool					_selectReso;
	bool					_switchRes;
	bool					_fullscreen;
};

#endif
