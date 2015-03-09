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
            if (p.grounded())
                p.setStence(Stence::Stand);
            else
                p.setStence(Stence::Jump);
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
    std::cout << "----------------" << std::endl;
    std::cout << "Old Stence: " << static_cast<int>(p.oldStence()) << " Stence: " << static_cast<int>(p.stence()) << std::endl;
    std::cout << "Transition launched: " << static_cast<int>(p.oldStence()) << " to " << static_cast<int>(p.stence()) << std::endl;
    std::cout << "Begin sprite id: " << begin << std::endl;
    std::cout << "Numbers of sprites: " << length << std::endl;
    std::cout << "Frame length: " << frames << std::endl;
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
    std::cout << "----------------" << std::endl;
    std::cout << "Old Stence: " << static_cast<int>(p.oldStence()) << " Stence: " << static_cast<int>(p.stence()) << std::endl;
    std::cout << "Animation launched: " << static_cast<int>(p.stence()) << std::endl;
    std::cout << "Begin sprite id: " << begin << std::endl;
    std::cout << "Numbers of sprites: " << length << std::endl;
    std::cout << "Frame length: " << frames << std::endl;
    //
    p.setAnimation(begin, length, frames);
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

    //update stence
    updatePlayerStence(p);
    if (p.oldStence() != p.stence())
        setPlayerTransition(p);
    if (p.finished() && !p.animation())
        setPlayerAnimation(p);

    // Final goal :
    //      Set new direction
    //      Set new stence
    //      Set new animation/transition if needed according to stence and direction
    //      Set new speed vector
    //      Set player position according to speed vector

    // All new parameters can be the same as before.
}
