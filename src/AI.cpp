#include "AI.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Map.hpp"

static int
abyssLen(int x, int y, const Map& map)
{
    int deep = 0;

    while (map.indexAt(x, y) == 0)
    {
        y--;
        deep++;
        if (y < 0)
            return 1000;
    }
    return deep;
}

void
AI::basic(Entity& entity, Player& player, const Map& map)
{
    lm::Vector2f center = entity.center();

	entity.setKey(Entity::Key::A, false);
	entity.setKey(Entity::Key::Left, false);
	entity.setKey(Entity::Key::Right, false);
	entity.setKey(Entity::Key::Space, false);

    if (lm::dist(player.position, entity.position) > 8.0f)
        return;

	if (player.dead())
		return;

	if (entity.position.x < player.position.x - 1)
	{
        if (abyssLen(center.x + 1, center.y, map) <= 9 || !entity.grounded)
        {
            if (entity.hp() > 10)
                entity.setKey(Entity::Key::Right, true);
            else
                entity.setKey(Entity::Key::Left, true);
        }
	}
	else if (entity.position.x > player.position.x + 1)
	{
        if (abyssLen(center.x, center.y, map) <= 9 || !entity.grounded)
        {
            if (entity.hp() > 10)
                entity.setKey(Entity::Key::Left, true);
            else
                entity.setKey(Entity::Key::Right, true);
        }
	}
	if (std::abs(entity.position.x - player.position.x) < 1.5f
        && std::abs(entity.position.y - player.position.y) <= 3.0f 
        && entity.grounded
        && std::rand() % 32 == 0)
	{
		if (entity.position.x < player.position.x)
			entity.setKey(Entity::Key::Right, true);
		else
			entity.setKey(Entity::Key::Left, true);
		entity.setKey(Entity::Key::A, true);
	}
    else if (entity.position.y < player.position.y - 1.0f
             && entity.position.y + 5.0f >= player.position.y
             && std::abs(entity.position.x - player.position.x) > 1.5f
             && std::rand() % 30 == 0)
    {
        entity.setKey(Entity::Key::Space, true);
    }
}

void
AI::boss(Entity& entity, Player& player, const Map& map)
{
    lm::Vector2f center = entity.center();
    
    entity.setKey(Entity::Key::A, false);
    entity.setKey(Entity::Key::Left, false);
    entity.setKey(Entity::Key::Right, false);

    if (lm::dist(player.position, entity.position) > 12.0f || player.dead())
        return;
    if (entity.position.x < player.position.x - 1)
    {
        if (abyssLen(center.x + 1, center.y, map) <= 9)
            entity.setKey(Entity::Key::Right, true);
    }
    else if (entity.position.x > player.position.x + 1)
    {
        if (abyssLen(center.x, center.y, map) <= 9)
            entity.setKey(Entity::Key::Left, true);
    }
    if (std::abs(entity.position.x - player.position.x) < 1.5f
        && std::abs(entity.position.y - player.position.y) <= 3.0f)
    {
        if (entity.position.x < player.position.x)
            entity.setKey(Entity::Key::Right, true);
        else
            entity.setKey(Entity::Key::Left, true);
        entity.setKey(Entity::Key::A, true);
    }
}
