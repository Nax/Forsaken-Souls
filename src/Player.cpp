#include "Player.hpp"
#include "Level.hpp"
#include "Screen.hpp"
#include "Tile.hpp"


Player::Player()
: IEntity(0, 5, 5)
{

}

void
Player::update(const Map& map)
{
	int a = 0;
	const bool jump = _keys[Key::Space];
	const bool attack = _keys[Key::A];
	if (_keys[Key::Left])
		a--;
	if (_keys[Key::Right])
		a++;

	if (dead())
		a = 0;
	if (_state != 6)
	{
		switch (a)
		{
			case -1:
				aim(Aim::Left);
				break;
			case 0:
				aim(Aim::None);
				break;
			case 1:
				aim(Aim::Right);
				break;
		}
	}
	if (dead())
		setState(5);
	else
	{
		if (_state == 6)
		{
			if (_sprite.finished())
				setState(0);
		}
		else if (!grounded)
		{
			if (speed.y > 0)
				setState(3);
			else
				setState(4);
		}
		else
		{
			if (jump)
				setState(3);
			else if (attack)
				setState(6);
			else if (a)
				setState(1);
			else
				setState(0);
		}
	}
	IEntity::update(map);
}

Player::~Player()
{

}
