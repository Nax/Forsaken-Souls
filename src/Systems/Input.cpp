#include "Systems/Input.hpp"
#include "Components/Input.hpp"

using namespace System;

Input::Input()
{

}

void
Input::operator()(std::vector<lm::GameObject*>& gameObjects, const lm::Event& event)
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

Input::~Input()
{
    
}
