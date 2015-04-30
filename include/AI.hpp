#ifndef AI_HPP
#define AI_HPP

class Entity;
class Player;
class Map;

namespace AI
{
	typedef void (*function)(Entity& entity, Player& player, const Map& map);

	void	basic(Entity& entity, Player& player, const Map& map);
    void    boss(Entity& entity, Player& player, const Map& map);
}

#endif