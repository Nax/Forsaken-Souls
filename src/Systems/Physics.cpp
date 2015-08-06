#include <cmath>
#include "Systems/Physics.hpp"

#include <iostream>

using namespace System;

Physics::Physics()
{

}

void
Physics::update(const Map& map)
{
    for (auto go : lm::GameObjectSet::instance())
    {
        auto* physics = go->getComponent<Component::Physics>("physics");
        if (physics)
            move(*go, *physics);
    }
    for (auto go : lm::GameObjectSet::instance())
    {
        auto* collider = go->getComponent<Component::Collider>("collider");
        if (collider)
            collide(*go, *collider, map);
    }
}

Physics::~Physics()
{
    
}

/* Private */

void
Physics::move(lm::GameObject& go, Component::Physics& physics)
{
    physics.speed.y -= 0.3f;
}

static void
collisions(int axis, lm::GameObject& go, const Map& map, lm::Vector2f& speed, Component::Collider& collider, Component::Physics& physics)
{
    if (axis == 1)
       physics.grounded = false;
    redo:
    lm::Rect2f  bb = collider.boundingBox;
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
                go.position[axis] -= diff;
                bb.pos[axis] -= diff;
                if (axis == 1 && !faceRight)
                    physics.grounded = true;
                speed[axis] = 0.0f;
                goto redo;
            }
        }
    }
}

void
Physics::collide(lm::GameObject& go, Component::Collider& collider, const Map& map)
{
    auto* physics = go.getComponent<Component::Physics>("physics");
    lm::Vector2f speed = physics->speed;
    go.position.x += speed.x * (1.f / 120.f);
    collisions(0, go, map, speed, collider, *physics);
    go.position.y += speed.y * (1.f / 120.f);
    collisions(1, go, map, speed, collider, *physics);
    physics->speed = speed;
}
