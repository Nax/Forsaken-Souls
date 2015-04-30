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
    lm::Vector2f e = entity.center();
    lm::Vector2f p = player.center();

	entity.setKey(Entity::Key::A, false);
	entity.setKey(Entity::Key::Left, false);
	entity.setKey(Entity::Key::Right, false);
	entity.setKey(Entity::Key::Space, false);

    if (lm::dist(e, p) > 8.0f)
        return;

	if (player.dead())
		return;

	if (e.x < p.x - 1)
	{
        if (abyssLen(e.x + 1, e.y, map) <= 9 || !entity.grounded)
        {
            if (entity.hp() > 10)
                entity.setKey(Entity::Key::Right, true);
            else
                entity.setKey(Entity::Key::Left, true);
        }
	}
	else if (e.x > p.x + 1)
	{
        if (abyssLen(e.x, e.y, map) <= 9 || !entity.grounded)
        {
            if (entity.hp() > 10)
                entity.setKey(Entity::Key::Left, true);
            else
                entity.setKey(Entity::Key::Right, true);
        }
	}
	if (std::abs(e.x - p.x) < 1.5f
        && std::abs(e.y - p.y) <= 3.0f 
        && entity.grounded
        && std::rand() % 32 == 0)
	{
		if (e.x < p.x)
			entity.setKey(Entity::Key::Right, true);
		else
			entity.setKey(Entity::Key::Left, true);
		entity.setKey(Entity::Key::A, true);
	}
    else if (e.y < p.y - 1.0f
             && e.y + 5.0f >= p.y
             && std::abs(e.x - p.x) > 1.5f
             && std::rand() % 30 == 0)
    {
        entity.setKey(Entity::Key::Space, true);
    }
}

void
AI::boss(Entity& entity, Player& player, const Map& map)
{
    lm::Vector2f e = entity.center();
    lm::Vector2f p = player.center();

    entity.setKey(Entity::Key::A, false);
    entity.setKey(Entity::Key::Left, false);
    entity.setKey(Entity::Key::Right, false);

    if (lm::dist(p, e) > 12.0f || player.dead())
        return;
    if (e.x < p.x - 1)
    {
        if (abyssLen(e.x + 1, e.y, map) <= 9)
            entity.setKey(Entity::Key::Right, true);
    }
    else if (e.x > p.x + 1)
    {
        if (abyssLen(e.x, e.y, map) <= 9)
            entity.setKey(Entity::Key::Left, true);
    }
    if (std::abs(e.x - p.x) < 1.5f
        && std::abs(e.y - p.y) <= 3.0f)
    {
        if (e.x < p.x)
            entity.setKey(Entity::Key::Right, true);
        else
            entity.setKey(Entity::Key::Left, true);
        entity.setKey(Entity::Key::A, true);
    }
}
