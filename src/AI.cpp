#include "AI.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Map.hpp"

void
AI::basic(Entity& entity, Player& player, const Map& map)
{
	entity.setKey(Entity::Key::A, false);
	entity.setKey(Entity::Key::Left, false);
	entity.setKey(Entity::Key::Right, false);
	entity.setKey(Entity::Key::Space, false);

	if (entity.position.x < player.position.x - 1)
	{
		entity.setKey(Entity::Key::Right, true);
	}
	else if (entity.position.x > player.position.x + 1)
	{
		entity.setKey(Entity::Key::Left, true);
	}
	if (entity.position.dist(player.position) < 2)
	{
		if (entity.position.x < player.position.x)
			entity.setKey(Entity::Key::Right, true);
		else
			entity.setKey(Entity::Key::Left, true);
		entity.setKey(Entity::Key::A, true);
	}
	else if (entity.position.y < player.position.y)
	{
		entity.setKey(Entity::Key::Space, true);
	}
}
