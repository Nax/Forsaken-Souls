#include <cmath>
#include "Systems/Physics.hpp"

using namespace System;

Physics::Physics()
{

}

void
Physics::update(std::vector<lm::GameObject*>& gameObjects, const Map& map)
{
    for (auto go : gameObjects)
    {
        auto* movable = static_cast<Component::Movable*>(go->getComponent("movable"));
        if (movable)
            move(*go, *movable);
    }
    for (auto go : gameObjects)
    {
        auto* collidable = static_cast<Component::Collidable*>(go->getComponent("collidable"));
        if (collidable)
            collide(*go, *collidable, map);
    }
}

Physics::~Physics()
{
    
}

/* Private */

void
Physics::move(lm::GameObject& go, Component::Movable& movable)
{
    movable.speed.x = movable.speed.x * 0.5f + (movable.data->speed.x * 0.5f) * ((movable.direction) ? 1.f : -1.f) * (movable.moving ? 1 : 0);
    movable.speed.y -= 0.3f;
}

static void
collisions(int axis, lm::GameObject& go, const Map& map, lm::Vector2f& speed, Component::Collidable& collidable)
{
    redo:
    lm::Rect2f  bb = *(collidable.currentBox);
    bb.pos += {go.position.x, go.position.y};
    const lm::Vector2f range = {std::ceil(bb.pos.x + bb.size.x), std::ceil(bb.pos.y + bb.size.y)};
    const bool faceRight = (speed[axis] >= 0.0f);

    for (int j = bb.pos.y; j < range.y; ++j)
    {
        for (int i = bb.pos.x; i < range.x; ++i)
        {
            const TileBoundingBox& tbb = map.at(i, j).boundingBoxes();

            for (int b = 0; b < tbb.count; ++b)
            {
                lm::Rect2f  tb = {{i + tbb.boxes[b].pos.x, j + tbb.boxes[b].pos.y}, {tbb.boxes[b].size.x, tbb.boxes[b].size.y}};
                float diff;

                if (tb.pos.x + tb.size.x < bb.pos.x || tb.pos.x > bb.pos.x + bb.size.x || tb.pos.y + tb.size.y < bb.pos.y || tb.pos.y > bb.pos.y + bb.size.y)
                    continue;
                if (faceRight)
                    diff = bb.pos[axis] + bb.size[axis] - tb.pos[axis];
                else
                    diff = bb.pos[axis] - (tb.pos[axis] + tb.size[axis]);
                std::cout << "axis :" << axis << " = " << diff << std::endl;
                go.position[axis] -= diff;
                bb.pos[axis] -= diff;
                if (axis == 1 && !faceRight)
                    go.send("switch_state", lm::sym("grounded"));
                speed[axis] = 0.0f;
                goto redo;
            }
        }
    }
}

void
Physics::collide(lm::GameObject& go, Component::Collidable& collidable, const Map& map)
{
    auto* movable = static_cast<Component::Movable*>(go.getComponent("movable"));
    lm::Vector2f speed = movable->speed;
    go.position.x += speed.x * (1.f / 120.f);
    collisions(0, go, map, speed, collidable);
    go.position.y += speed.y * (1.f / 120.f);
    collisions(1, go, map, speed, collidable);
    movable->speed = speed;
}
