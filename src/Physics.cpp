#include "Physics.hpp"

void
Phys::checkGrounded(Player &p)
{
    // Tile should be an arg

    // Get map portion just below the player.
    // Check collisions between p.boundingBox bottom side and tile bounding box.
    // if collision -> p.setGrounded(true);
    // else -> p.setGrounded(false);
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
}

void
Phys::setPlayerTransition(Player &p)
{
    p.setAnimation(false);
    p.setTransition(true);
    int begin = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].begin;
    int length = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].length;
    int frames = gEntityData[p.dataId()].transitions[static_cast<int>(p.oldStence())][static_cast<int>(p.stence())].frames;
    //
    // std::cout << "----------------" << std::endl;
    // std::cout << "Old Stence: " << static_cast<int>(p.oldStence()) << " Stence: " << static_cast<int>(p.stence()) << std::endl;
    // std::cout << "Transition launched: " << static_cast<int>(p.oldStence()) << " to " << static_cast<int>(p.stence()) << std::endl;
    // std::cout << "Begin  id: " << begin << std::endl;
    // std::cout << "Numbers of sprites: " << length << std::endl;
    // std::cout << "Frame length: " << frames << std::endl;
    //
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
    //
    // std::cout << "----------------" << std::endl;
    // std::cout << "Old Stence: " << static_cast<int>(p.oldStence()) << " Stence: " << static_cast<int>(p.stence()) << std::endl;
    // std::cout << "Animation launched: " << static_cast<int>(p.stence()) << std::endl;
    // std::cout << "Begin sprite id: " << begin << std::endl;
    // std::cout << "Numbers of sprites: " << length << std::endl;
    // std::cout << "Frame length: " << frames << std::endl;
    //
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
Phys::updatePlayerPosition(Player &p)
{
    double  x, y;
    bool    collisionX = false, collisionY = false;

    x = p.x() + p.speed().x * 2.0;
    y = p.y() - p.speed().y * 2.0;


    // checkForCollision();
    if (!collisionX)
        p.setX(x);
    if (!collisionY)
        p.setY(y);

}

void
Phys::updatePlayer(Player &p)
{
    bool    moving;
    bool    turning;

    p.setOldDir();
    p.setOldStence();
    checkGrounded(p);

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
    updatePlayerPosition(p);

    // Final goal :
    //      Set new direction
    //      Set new stence
    //      Set new animation/transition if needed according to stence and direction
    //      Set new speed vector
    //      Set player position according to speed vector

    // All new parameters can be the same as before.
}
