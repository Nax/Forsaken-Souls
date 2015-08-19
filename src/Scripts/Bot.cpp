#include "Scripts/Bot.hpp"
#include "Components/Physics.hpp"
#include "Components/Collider.hpp"
#include "Components/Skeleton.hpp"
#include "Level.hpp"
#include "Map.hpp"
#include "AStar.hpp"
#include "Physics.hpp"

#include <cmath>
#include <list>
#include <vector>
#include <iostream>

LUMS_REGISTER_COMPONENT(Script::Bot, "script_bot");

using namespace Script;

static float
heightAt(const Map& map, lm::Vector2f position)
{
    int x = position.x;
    int y = position.y;

    if (map.indexAt(x, y) != 0)
        return y;

    while (map.indexAt(x, y) == 0)
    {
        y--;
        if (y == -1)
            return -1.f;
    }
    return float(y + 1);
}

class BotFunctor
{
public:
    BotFunctor(Component::Collider& collider)
    : _collider(collider)
    {
        lm::SfxProvider::instance().get("footstep_common_bot").setVolume(0.3f);
    }

    void
    operator()(AStar& astar, AStarNode& node)
    {
        const Map& map = Level::instance().map();
        walk(astar, node, map, -1.5f);
        walk(astar, node, map, 1.5f);
        fall(astar, node, map, -Bot::moveSpeed);
        fall(astar, node, map, Bot::moveSpeed);
        jump(astar, node, map, {-Bot::moveSpeed, Bot::jumpSpeed});
        jump(astar, node, map, {Bot::moveSpeed, Bot::jumpSpeed});
    }

    void
    walk(AStar& astar, AStarNode& node, const Map& map, float delta)
    {
        lm::Vector2f position = node.position;
        position.x += delta;
        position.y += 0.01f;
        lm::Rect2f boundingBox = _collider.boundingBox;
        boundingBox.pos += position;
        if (map.indexAt(position.x, position.y - 1) == 0)
            return;
        if (Physics::intersect(map, boundingBox))
            return;
        astar.addOpenNode(&node, position, 0);
    }

    void
    fall(AStar& astar, AStarNode& node, const Map& map, float speed)
    {
        lm::Vector2f position = node.position;
        lm::Rect2f boundingBox = _collider.boundingBox;
        boundingBox.pos += position;
        lm::Vector2f finalPos;
        int frames;
        if (!Physics::computeFinalPosition(finalPos, frames, map, boundingBox, {speed, 0}))
            return;
        astar.addOpenNode(&node, finalPos - _collider.boundingBox.pos, 0);
    }

    void
    jump(AStar& astar, AStarNode& node, const Map& map, lm::Vector2f speed)
    {
        lm::Vector2f position = node.position;
        lm::Rect2f boundingBox = _collider.boundingBox;
        boundingBox.pos += position;
        lm::Vector2f finalPos;
        int frames;
        if (!Physics::computeFinalPosition(finalPos, frames, map, boundingBox, speed))
            return;
        float penality = (10.f - 3 * fabs(finalPos.x - boundingBox.pos.x)) / 10.f;
        if (penality < 0.1f)
            penality = 0.1f;
        astar.addOpenNode(&node, finalPos - _collider.boundingBox.pos, 1, penality);
    }

private:
    Component::Collider&  _collider;
};

void
Bot::init(lm::GameObject& object)
{
    _targeting = false;
}

void
Bot::update(lm::GameObject& object)
{
    if (!_targeting)
        findPath(object);
    move(object);
    playSfx(object);
    setAnimation(object);
}

void
Bot::move(lm::GameObject& object)
{
    auto physics = object.getComponent<::Component::Physics>("physics");
    lm::Vector2f velocity = physics->speed;

    if (!_targeting)
    {
        velocity.x = 0.f;
        return;
    }
    if (physics->grounded && _targetType == 1)
        velocity.y = jumpSpeed;
    if (object.position.x < _target.x)
        velocity.x = moveSpeed;
    else if (object.position.x > _target.x)
        velocity.x = -moveSpeed;
    if (lm::dist({object.position.x, object.position.y}, _target) < 0.5f)
        _targeting = false;
    physics->speed = velocity;
}

void
Bot::findPath(lm::GameObject& object)
{
    lm::GameObject* player = lm::GameObjectSet::instance().getObjectByTag("player");
    auto physics = object.getComponent<::Component::Physics>("physics");
    auto collider = object.getComponent<::Component::Collider>("collider");
    if (!physics->grounded)
        return;
    if (!player)
        return;
    AStar astar({object.position.x, object.position.y}, {player->position.x, player->position.y});
    AStarNode targetNode;
    BotFunctor functor(*collider);
    if (!astar.getPath(targetNode, functor))
        return;
    _targeting = true;
    _target = targetNode.position;
    _targetType = targetNode.type;
}

void
Bot::setAnimation(lm::GameObject& object)
{
    auto physics = object.getComponent<::Component::Physics>("physics");
    auto skeleton = object.getComponent<::Component::Skeleton>("skeleton");
    auto& sk = skeleton->skeleton();

    if (!physics->grounded)
        sk.setAnimation("Fall", true);
    else if (physics->speed.x > 0.01f)
    {
        sk.setAnimation("Run", true);
        sk.setFlip(true);
    }
    else if (physics->speed.x < -0.01f)
    {
        sk.setAnimation("Run", true);
        sk.setFlip(false);
    }
    else
        sk.setAnimation("Idle_Wait", true);

}

void
Bot::playSfx(lm::GameObject& object)
{
    auto skeleton = object.getComponent<::Component::Skeleton>("skeleton");
    auto& sk = skeleton->skeleton();

    if (sk.event() == lm::sym("Event_FootStep"))
        lm::SfxProvider::instance().get("footstep_common_bot").play();
}
