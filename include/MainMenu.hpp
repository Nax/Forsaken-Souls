#ifndef MAIN_MENU
#define MAIN_MENU

#include <Lums>

class MainMenu : public lm::GameState
{
public:
    MainMenu();
    void load();
    void handleEvent(const lm::Event& event);
    void update();
    void render();
    void unload();
    ~MainMenu();

private:
    void moveCursor(int direction);

    lm::StaticSpriteBatch   _newGameBatch;
    lm::StaticSpriteBatch   _quitBatch;
    lm::StaticSpriteBatch   _cursorBatch;
    lm::Projection          _proj;
    int                     _cursor;
};

#endif
