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
                p.setStence(Stence::Stand);
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
Phys::setPlayerTransitionFromStand(Player &p)
{
    switch (p.stence())
    {
        case Stence::Run:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Crouch:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Jump:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Secret:
            // p.setAnimation(start, end, frames, true);
            break;
        default:
            break;
    }
}

void
Phys::setPlayerTransitionFromRun(Player &p)
{
    switch (p.stence())
    {
        case Stence::Stand:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Crouch:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Jump:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Secret:
            // p.setAnimation(start, end, frames, true);
            break;
        default:
            break;
    }
}

void
Phys::setPlayerTransitionFromCrouch(Player &p)
{
    switch (p.stence())
    {
        case Stence::Stand:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Run:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Jump:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Secret:
            // p.setAnimation(start, end, frames, true);
            break;
        default:
            break;
    }
}

void
Phys::setPlayerTransitionFromJump(Player &p)
{
    switch (p.stence())
    {
        case Stence::Stand:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Run:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Crouch:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Secret:
            // p.setAnimation(start, end, frames, true);
            break;
        default:
            break;
    }
}

void
Phys::setPlayerTransitionFromSecret(Player &p)
{
    switch (p.stence())
    {
        case Stence::Stand:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Run:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Crouch:
            // p.setAnimation(start, end, frames, true);
            break;
        case Stence::Jump:
            // p.setAnimation(start, end, frames, true);
            break;
        default:
            break;
    }
}

void
Phys::setPlayerTransition(Player &p)
{
    if (p.transition())
        return;
    switch (p.oldStence())
    {
        case Stence::Stand:
            setPlayerTransitionFromStand(p);
            break;
        case Stence::Run:
            setPlayerTransitionFromRun(p);
            break;
        case Stence::Crouch:
            setPlayerTransitionFromCrouch(p);
            break;
        case Stence::Jump:
            setPlayerTransitionFromJump(p);
            break;
        case Stence::Secret:
            setPlayerTransitionFromSecret(p);
            break;
        default:
            break;
    }
}

void
Phys::setPlayerAnimation(Player &p)
{
    switch (p.stence())
    {
        case Stence::Stand:
            // p.setAnimation(start, end, frame);
            break;
        case Stence::Run:
            // p.setAnimation(start, end, frame);
            break;
        case Stence::Crouch:
            // p.setAnimation(start, end, frame);
            break;
        case Stence::Jump:
            // p.setAnimation(start, end, frame);
            break;
        case Stence::Secret:
            // p.setAnimation(start, end, frame);
            break;
    }
}

void
Phys::updatePlayer(Player &p)
{
    bool    moving;
    bool    turning;

    checkGrounded(p);
    p.setOldDir();
    p.setOldStence();

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
