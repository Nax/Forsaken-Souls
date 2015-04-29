#ifndef MAIN_MENU
#define MAIN_MENU

#include <Lums/Lums.hpp>

#define MIN_CURSOR 0
#define MAX_CURSOR 1

class MainMenu : public lm::GameState
{
public:
    MainMenu();
    // void load();
    void handleEvent(const lm::Event& event);
    void update();
    void render();
    // void unload();
    ~MainMenu();
private:
    short   _cursor;
    short   _inhibitStik;
};

#endif