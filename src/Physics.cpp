#include "Physics.hpp"
#include "Level.hpp"

void
Phys::checkGrounded(Player &p, const Map& map)
{
    bool    grounded;

    double x0 = p.x();
    double x1 = p.x() + gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    double y = p.y() + gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];
    int ox0 = static_cast<int>(x0);
    int ox1 = static_cast<int>(x1);
    int oy = static_cast<int>(y);

    for (int k = ox0; k <= ox1; k++)
    {
        const TileBoundingBox& tile = map.at(k, oy).boundingBoxes();
        for (int i = 0; i < tile.count; i++)
        {
            if (y > tile.boxes[i].y)
            {
                p.setGrounded(true);
                return;
            }
        }
    }
    p.setGrounded(false);
}

void
Phys::updatePlayerStence(Player &p)
{
    switch (p.oldStence())
    {
        case Stence::Stand:
        {
            if (p.key(KeyId::Space))
                p.setStence(Stence::Jump);
            else if (p.key(KeyId::Left) || p.key(KeyId::Right))
                p.setStence(Stence::Run);
            else if (p.key(KeyId::Down))
                p.setStence(Stence::Crouch);
            else
                p.setStence(Stence::Stand);
            break;
        }
        case Stence::Run:
        {
            if (p.key(KeyId::Space))
                p.setStence(Stence::Jump);
            else if ((p.oldDir() == false && p.key(KeyId::Left) == false) || (p.oldDir() == true && p.key(KeyId::Right) == false))
                p.setStence(Stence::Stand);
            else if (p.key(KeyId::Down))
                p.setStence(Stence::Crouch);
            else
                p.setStence(Stence::Run);
            break;
        }
        case Stence::Crouch:
        {
            if (p.key(KeyId::Space))
                p.setStence(Stence::Jump);
            if (p.key(KeyId::Down) == false)
                p.setStence(Stence::Stand);
            else
                p.setStence(Stence::Crouch);
            break;
        }
        case Stence::Jump:
        {
            //
            p.setGrounded(false);
            //
            if (p.speed().y < 0.0)
                p.setStence(Stence::Fall);
            else
                p.setStence(Stence::Jump);
            break;
        }
        case Stence::Fall:
        {
            if (p.grounded())
                p.setStence(Stence::Stand);
            else
                p.setStence(Stence::Fall);
            break;
        }
        case Stence::Secret:
            break;
        default:
            break;
    }
    if (!p.grounded())
    {
        if (p.speed().y > 0)
            p.setStence(Stence::Jump);
        else
            p.setStence(Stence::Fall);
    }
}

void
Phys::setPlayerTransition(Player &p)
{
    p.setAnimation(false);
    p.setTransition(true);
    int begin = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].begin;
    int length = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].length;
    int frames = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].frames;
    p.setAnimation(begin, length, frames, false);
}

void
Phys::setPlayerAnimation(Player &p)
{
    p.setAnimation(true);
    p.setTransition(false);
    int begin = gEntityData[p.dataId()].animations[static_cast<int>(p.stence())].begin;
    int length = gEntityData[p.dataId()].animations[static_cast<int>(p.stence())].length;
    int frames = gEntityData[p.dataId()].animations[static_cast<int>(p.stence())].frames;
    p.setAnimation(begin, length, frames);
}

void
Phys::updatePlayerSpeed(Player &p, bool moving)
{
    double      factor = (p.direction()) ? 1.0 : -1.0;
    Stence      stence = p.stence();

    // y speed
    if (p.grounded())
    {
        if (stence == Stence::Jump)
            p.setSpeed(p.speed().x, 1.0);
        else
            p.setSpeed(p.speed().x, 0.0);
    }
    else
        p.setSpeed(p.speed().x, fmax((p.speed().y - 0.02), -2.0));

    // x speed
    if (p.grounded())
    {
        if (stence == Stence::Stand || stence == Stence::Crouch)
            p.setSpeed(0.0, 0.0);
        else if (stence == Stence::Run)
            p.setSpeed(factor * 1.0, 0.0);
        else
            p.setSpeed(factor * 0.7, p.speed().y);
    }
    else
    {
        if (moving)
            p.setSpeed(factor * 0.7, p.speed().y);
        else
            p.setSpeed(0.0, p.speed().y);
    }
}

void
Phys::updatePlayerPosition(Player &p, const Map& map)
{
    double  newX = p.x() + p.speed().x * 0.1;
    double  newY = p.y() - p.speed().y * 0.1;
    
    double x0 = newX;
    double x1 = newX + gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][0];
    double y0 = newY;
    double y1 = newY + gEntityData[p.dataId()].boundingBox[static_cast<int>(p.stence())][1];

    int ox0 = static_cast<int>(x0);
    int ox1 = static_cast<int>(x1);
    int oy0 = static_cast<int>(y0);
    int oy1 = static_cast<int>(y1);

    oy1 = (p.grounded()) ? oy1 - 1 : oy1;

    bool    collisionX = false, collisionY = false;

    // check for X collision
    if (p.speed().x != 0)
    {
        for (int i = oy0; i <= oy1; i++)
        {
            if (collisionX)
                break;

            // check for left collision
            if (p.speed().x < 0)
            {
                const TileBoundingBox& left = map.at(ox0, i).boundingBoxes();
                for (int k = 0; k < left.count; k++)
                {
                    std::cout << "LEFT CHECKING" << std::endl << "newX: " << newX << "  left x: " << left.boxes[k].x << std::endl;
                    if (x0 < ox0 + left.boxes[k].x + left.boxes[k].w)
                    {
                        collisionX = true;
                        break;
                    }
                }
            }
            // check for right collision
            else
            {
                const TileBoundingBox& right = map.at(ox1, i).boundingBoxes();
                for (int k = 0; k < right.count; k++)
                {
                    std::cout << "RIGHT CHECKING" << std::endl <<  "newX: " << x1 << "  right x: " << ox1 + right.boxes[k].x << std::endl;
                    if (x1 > ox1 + right.boxes[k].x)
                    {
                        collisionX = true;
                        break;
                    }
                }
            }
        }
    }

    // check for Y collision
    // blabla

    if (!collisionX)
        p.setX(newX);
    if (!collisionY)
        p.setY(newY);
}

void
Phys::updatePlayer(Player &p, const Map& map)
{
    bool    moving;
    bool    turning;

    p.setOldDir();
    p.setOldStence();
    checkGrounded(p, map);

    // update direction
    moving = (p.key(KeyId::Left) && !p.key(KeyId::Right)) || (p.key(KeyId::Right) && !p.key(KeyId::Left));
    if (moving)
        p.key(KeyId::Left) ? p.setDirection(false) : p.setDirection(true);
    p.flipX(!p.direction());

    // update stence
    updatePlayerStence(p);
    if (p.oldStence() != p.stence())
        setPlayerTransition(p);
    if (p.finished() && !p.animation())
        setPlayerAnimation(p);

    updatePlayerSpeed(p, moving);
    updatePlayerPosition(p, map);

    // Final goal :
    //      Set new direction
    //      Set new stence
    //      Set new animation/transition if needed according to stence and direction
    //      Set new speed vector
    //      Set player position according to speed vector

    // All new parameters can be the same as before.
}
