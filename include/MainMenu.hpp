#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <Lums/Lums.hpp>

class MainMenu : public lm::GameState
{
public:
    MainMenu();
    void    load();
    void    update();
    void    handleEvent(const lm::Event& event);
    void    render() const;
    void    unload();
    ~MainMenu();

private:
    lm::Sprite  _background;
    lm::Sprite  _title;
    size_t      _alpha;
};

#endif