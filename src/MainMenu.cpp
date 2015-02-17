#include "MainMenu.hpp"
#include "ImageProvider.hpp"

MainMenu::MainMenu()
: _alpha(0)
{

}

void
MainMenu::load()
{
    auto& bg = ImageProvider::get().loadImage(ImageID::MenuBackground);
    auto& title = ImageProvider::get().loadImage(ImageID::MenuTitle);

    _background.setImage(bg);
    _title.setImage(title);
}

void
MainMenu::update()
{
    if (_alpha < 255)
        _alpha++;
}

void
MainMenu::handleEvent(const lm::Event& event)
{
    if (event.type == lm::Event::Type::KeyDown
        && event.key == lm::Key::Escape)
        lm::Core::get().stop();
}

void
MainMenu::render() const
{
    _background.draw();
    glColor4ub(255, 255, 255, _alpha);
    _title.draw(512 - _title.width() / 2, 100);
    glColor4f(1, 1, 1, 1);
}

void
MainMenu::unload()
{
    ImageProvider::get().unloadImage(ImageID::MenuBackground);
    ImageProvider::get().unloadImage(ImageID::MenuTitle);
}

MainMenu::~MainMenu()
{

}
