#include <cmath>
#include <iostream>
#include "Physics.hpp"
#include "Level.hpp"
#include "Screen.hpp"
#include <vector>

std::vector<lm::VertexArrayc<4>> debugPhysics;

void
Phys::updatePlayer(Player &p, const Map& map)
{
    debugPhysics.clear();
    std::cout << "===================" << std::endl;

    p.setOldStance();
    p.setOldDir();

    // update player position
    applyGravity(p);
    updatePosition(p);

    // set player position/speed according to collisions
    float dx = 0.0;
    float dy = 0.0;
    checkCollisionX(p, map, &dx);
    checkCollisionY(p, map, &dy);

    if (fabs(dy) < fabs(dx) && dy != 0.f)
    {
        std::cout << "Y" << std::endl;
        
        p.position.y += dy;
        p.speed = {p.speed.x, 0.f};
        if (dy > 0.f)
            p.grounded = true;

        checkCollisionX(p, map, &dx);
        p.position.x += dx;
        if (dx != 0.f)
        {
            std::cout << "X" << std::endl;
            p.speed = {0.f, p.speed.y};
        }
    }
    else if (dx != 0.f)
    {
        std::cout << "X" << std::endl;
        
        p.position.x += dx;
        p.speed = {0.f, p.speed.y};

        checkCollisionY(p, map, &dy);
        p.position.y += dy;
        if (dy != 0.f)
        {
            std::cout << "Y" << std::endl;
            p.speed = {p.speed.x, 0.f};
        }
        if (dy > 0.f)
            p.grounded = true;
    }

    updateSpeed(p);
    updateStance(p);

    std::cout << "===================" << std::endl;
}

void
Phys::updatePosition(Player& p)
{
    p.position.x = p.position.x + p.speed.x * 0.1f;
    p.position.y = p.position.y + p.speed.y * 0.1f;
}

void
Phys::updateSpeed(Player& p)
{
    if (p.grounded)
    {
        if (p.key(KeyId::Space))
            p.speed.y = 1.f;
        if (p.key(KeyId::Right) && !p.key(KeyId::Left))
            p.speed.x = 0.7f;
        if (p.key(KeyId::Left) && !p.key(KeyId::Right))
            p.speed.x = -0.7f;
        if (p.key(KeyId::Down))
            p.speed.x = 0.f;
    }
    else
    {
        if (p.key(KeyId::Right) && !p.key(KeyId::Left))
            p.speed.x = 0.5f;
        if (p.key(KeyId::Left) && !p.key(KeyId::Right))
            p.speed.x = -0.5f;
    }
    if (p.speed.x != 0.f && !p.key(KeyId::Right) && !p.key(KeyId::Left))
        p.speed.x = 0.f;
}
void
Phys::updateStance(Player& p)
{
    if (p.speed.x < 0)
        p.setDirection(false);
    else if (p.speed.x > 0)
        p.setDirection(true);

    if (p.grounded)
    {
        if (p.speed.x != 0.f)
            p.setStance(Stance::Run);
        else
            p.setStance(Stance::Stand);
    }
    else
    {
        if (p.speed.y > 0.f)
            p.setStance(Stance::Jump);
        else
            p.setStance(Stance::Fall);
    }

    p.setAnimation(true);
    p.setTransition(false);
    int begin = gEntityData[p.dataId()].animations[static_cast<int>(p.stance())].begin;
    int length = gEntityData[p.dataId()].animations[static_cast<int>(p.stance())].length;
    int frames = gEntityData[p.dataId()].animations[static_cast<int>(p.stance())].frames;

    if (p.oldStance() != p.stance())
        p.setAnimation(begin, length, frames);
}


void
Phys::applyGravity(Player& p)
{
    p.grounded = false;
    p.speed = {p.speed.x, fmaxf((p.speed.y - 0.02f), -2.f)};
    // p.speed = {0.4f, p.speed.y};
}

void
Phys::checkCollisionY(Player& p, const Map& map, float* dy)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stance())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stance())][1];

    *dy = 0.f;

    // check for downward collisions
    if (p.speed.y <= 0.f)
    {
        for (int i = p.position.x; i <= floor(p.position.x + w); i++)
        {
            const TileBoundingBox& box = map.at(i, p.position.y).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = i + box.boxes[j].x;
                float   by = floor(p.position.y) + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.x + w > bx && p.position.x < bx + bw && p.position.y + h > by && p.position.y < by + bh)
                {
                    lm::VertexArrayc<4> v;

                    v.push(bx * 32, SCREEN_HEIGHT - (by * 32), 1, 0, 0);
                    v.push((bx + bw) * 32, SCREEN_HEIGHT - (by * 32), 1, 0, 0);
                    v.push((bx + bw) * 32, SCREEN_HEIGHT - ((by + bh) * 32), 1, 0, 0);
                    v.push(bx * 32, SCREEN_HEIGHT - ((by + bh) * 32), 1, 0, 0);
                    debugPhysics.push_back(v);

                    if (fabs((by + bh) - p.position.y) > fabs(*dy))
                    {
                        *dy = (by + bh) - p.position.y;
                    }
                }
            }
        }
    }
    // check for upward collisions
    else
    {
        for (int i = p.position.x; i < ceil(p.position.x + w); i++)
        {
            const TileBoundingBox& box = map.at(i, p.position.y + h).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = i + box.boxes[j].x;
                float   by = floor(p.position.y + h) + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.x + w > bx && p.position.x < bx + bw && p.position.y + h > by && p.position.y < by + bh)
                {
                    lm::VertexArrayc<4> v;

                    v.push(i * 32, SCREEN_HEIGHT - (p.position.y + h) * 32, 1, 0, 0);
                    v.push((i + 1) * 32, SCREEN_HEIGHT - (p.position.y + h) * 32, 1, 0, 0);
                    v.push((i + 1) * 32, SCREEN_HEIGHT - ((p.position.y + h) + 1) * 32, 1, 0, 0);
                    v.push(i * 32, SCREEN_HEIGHT - ((p.position.y + h) + 1) * 32, 1, 0, 0);
                    debugPhysics.push_back(v);

                    if (fabs((by - h) - p.position.y) > fabs(*dy))
                    {
                        *dy = (by - h) - p.position.y;
                    }
                }
            }
        }
    }
}

void
Phys::checkCollisionX(Player& p, const Map& map, float* dx)
{
    float w = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stance())][0];
    float h = gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stance())][1];

    *dx = 0.f;

    // check for left collisions
    if (p.speed.x <= 0.f)
    {
        for (int i = p.position.y; i < ceil(p.position.y + h); i++)
        {
            const TileBoundingBox& box = map.at(p.position.x, i).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = floor(p.position.x) + box.boxes[j].x;
                float   by = i + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.y + h > by && p.position.y < by + bh && p.position.x + w > bx && p.position.x < bx + bw)
                {
                    lm::VertexArrayc<4> v;

                    v.push(p.position.x * 32, SCREEN_HEIGHT - i * 32, 1, 1, 0);
                    v.push((p.position.x - 1) * 32, SCREEN_HEIGHT - i * 32, 1, 1, 0);
                    v.push((p.position.x - 1) * 32, SCREEN_HEIGHT - (i + 1) * 32, 1, 1, 0);
                    v.push(p.position.x * 32, SCREEN_HEIGHT - (i + 1) * 32, 1, 1, 0);

                    debugPhysics.push_back(v);

                    if (fabs((bx + bw) - p.position.x) > fabs(*dx))
                    {
                        *dx = (bx + bw) - p.position.x;
                    }
                }
            }
        }
    }
    // check for right collisions
    else
    {
        for (int i = p.position.y; i < ceil
            (p.position.y + h); i++)
        {
            const TileBoundingBox& box = map.at(p.position.x + w, i).boundingBoxes();
            for (int j = 0; j < box.count; j++)
            {
                float   bx = floor(p.position.x + w) + box.boxes[j].x;
                float   by = i + box.boxes[j].y;
                float   bw = box.boxes[j].w;
                float   bh = box.boxes[j].h;

                if (p.position.y + h > by && p.position.y < by + bh && p.position.x + w > bx && p.position.x < bx + bw)
                {
                    lm::VertexArrayc<4> v;

                    v.push((p.position.x + w) * 32, SCREEN_HEIGHT - i * 32, 1, 1, 0);
                    v.push(((p.position.x + w) + 1) * 32, SCREEN_HEIGHT - i * 32, 1, 1, 0);
                    v.push(((p.position.x + w) + 1) * 32, SCREEN_HEIGHT - (i + 1) * 32, 1, 1, 0);
                    v.push((p.position.x + w) * 32, SCREEN_HEIGHT - (i + 1) * 32, 1, 1, 0);

                    debugPhysics.push_back(v);

                    if (fabs((bx - w) - p.position.x) > fabs(*dx))
                    {
                        *dx = (bx - w) - p.position.x;
                    }
                }
            }
        }
    }
}
