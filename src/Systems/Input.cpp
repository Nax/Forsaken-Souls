#include "Systems/Input.hpp"
#include "Components/Input.hpp"

using namespace System;

Input::Input()
{

}

void
Input::handleEvent(std::vector<lm::GameObject*>& gameObjects, const lm::Event& event)
{
    if (event.type != lm::Event::Type::KeyDown && event.type != lm::Event::Type::KeyUp)
        return;

    bool key = (event.type == lm::Event::Type::KeyDown);

    for (auto go : gameObjects)
    {
        auto component = static_cast<Component::Input*>(go->getComponent("input"));
        if (!component)
            continue;
        switch (event.key)
        {
            case lm::Key::Right:
                component->right = key;
                break;
            case lm::Key::Left:
                component->left = key;
                break;
            case lm::Key::Down:
                component->crouch = key;
                break;
            case lm::Key::Space:
                component->jump = key;
                break;
            case lm::Key::Q:
                component->meleeAttack = key;
                break;
            case lm::Key::W:
                component->rangeAttack = key;            
                break;
            default:
                break;
        } 
    }
}

void
Input::update(std::vector<lm::GameObject*>& gameObjects)
{
    for (auto go : gameObjects)
    {
        auto component = static_cast<Component::Input*>(go->getComponent("input"));
        if (!component)
            continue;
        if (component->left && !component->right)
            sendInput(*go, "left");
        else if (component->right && !component->left)
            sendInput(*go, "right");
        else
            sendInput(*go, "no_move");
        if (component->meleeAttack)
            sendInput(*go, "melee");
        if (component->jump)
            sendInput(*go, "jump");
    }
}

Input::~Input()
{
    
}

/* Private */

void
Input::sendInput(lm::GameObject& object, const char* str)
{
    object.send("switch_state", lm::sym(str));
}
