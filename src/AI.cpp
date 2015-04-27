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

	if (player.dead())
		return;

	if (entity.position.x < player.position.x - 1)
	{
		entity.setKey(Entity::Key::Right, true);
	}
	else if (entity.position.x > player.position.x + 1)
	{
		entity.setKey(Entity::Key::Left, true);
	}
	if (lm::dist(entity.position, player.position) < 2 && entity.grounded)
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
