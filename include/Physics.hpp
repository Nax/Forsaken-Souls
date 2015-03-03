#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Player.hpp"

namespace Phys
{

	void	updatePlayer(Player& p)
	{
		switch (p.stence())
		{
			case Stence::Stand:
			{
				if (p.speed().x != 0.0 || p.speed().y != 0.0)			
					p.setSpeed(0.0, 0.0);
				break;
			}
			case Stence::Run:
				break;
			case Stence::Crouch:
				break;
			case Stence::Jump:
				break;
			case Stence::Secret:
				break;
			default:
				break;
		}
	}
}

#endif