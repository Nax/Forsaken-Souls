#include "Scripts/Bot.hpp"
#include "Components/Physics.hpp"
#include "Components/Skeleton.hpp"
#include "Level.hpp"
#include "Map.hpp"

#include <cmath>
#include <list>
#include <vector>
#include <iostream>

LUMS_REGISTER_COMPONENT(Script::Bot, "script_bot");

using namespace Script;

struct TargetNode
{
    lm::Vector2f    position;
    Bot::TargetType type;
    TargetNode*     parent;
};

static float
pathLength(lm::Vector2f target, TargetNode& node)
{
    float length = lm::dist(target, node.position);
    TargetNode* n = &node;
    while (n->type != Bot::TargetType::None)
    {
        length += lm::dist(n->position, n->parent->position);
        n = n->parent;
    }
    return length;
}

void
Bot::init(lm::GameObject& object)
{
    _targeting = false;
}

void
Bot::update(lm::GameObject& object)
{
    auto* physics = object.getComponent<::Component::Physics>("physics");
    auto* skeleton = object.getComponent<::Component::Skeleton>("skeleton");

    if (_targeting)
    {
        float targetDist = lm::dist({object.position.x, object.position.y}, _target);
        if ((targetDist < 0.1f  && physics->grounded) || _lastTargetDist - targetDist < 0.001f)
        {
            _targeting = false;
            if (physics->grounded)
                findPath(object);
        }
        else
        {
            _lastTargetDist = targetDist;
            if (_targetType == Bot::TargetType::Jump)
            {
                if (physics->grounded)
                    physics->speed.y = 20.f;
                if (object.position.x < _target.x)
                {
                    physics->speed.x = 6.0f;
                    skeleton->skeleton().setFlip(true);
                    skeleton->skeleton().setAnimation("Run", true);
                }
                else
                {
                    physics->speed.x = -6.0f;
                    skeleton->skeleton().setFlip(false);
                    skeleton->skeleton().setAnimation("Run", true);
                }
            }
            else if (physics->grounded)
            {
                if (object.position.x < _target.x - 0.1f
                || (object.position.x < _target.x && physics->grounded && _targetType == Bot::TargetType::Fall))
                {
                    physics->speed.x = 6.0f;
                    skeleton->skeleton().setFlip(true);
                    skeleton->skeleton().setAnimation("Run", true);
                }
                else if (object.position.x > _target.x + 0.1f
                    || (object.position.x > _target.x && physics->grounded && _targetType == Bot::TargetType::Fall))
                {
                    physics->speed.x = -6.0f;
                    skeleton->skeleton().setFlip(false);
                    skeleton->skeleton().setAnimation("Run", true);
                }
                else
                {
                    physics->speed.x = 0.f;
                    skeleton->skeleton().setAnimation("Idle_Wait", true);
                }
            }
            else
            {
                physics->speed.x = 0.f;
                skeleton->skeleton().setAnimation("Idle_Wait", true);
            }
        }
    }
    else
    {
        physics->speed.x = 0.f;
        skeleton->skeleton().setAnimation("Idle_Wait", true);
        if (physics->grounded)
            findPath(object);
    }
    if (_targeting)
    {
        std::cout << "TARGET MODE" << std::endl;
        std::cout << "SELF: x:" << object.position.x << " y: " << object.position.y << std::endl;
        std::cout << "x: " << _target.x << " y: " << _target.y << std::endl;
    }
    else
        std::cout << "NO TARGET" << std::endl;
}

static bool
isNodeClosed(TargetNode& node, std::list<TargetNode*>& closedNodes)
{
    for (auto c : closedNodes)
    {
        if (lm::dist(c->position, node.position) < 0.05f)
            return true;
    }
    return false;
}

static float
computeDepth(const Map& map, lm::Vector2f position)
{
    float depth = 0.f;
    while (int(position.y) >= 0.5f)
    {
        if (map.indexAt(position.x, position.y - 0.5f))
            return depth;
        depth += 1.f;
        position.y -= 1.f;
    }
    return -1.f;
}

static lm::Vector2f
evaluateJump(const Map& map, lm::Vector2f position, lm::Vector2f speed)
{
    // We simulate 1000 frames of jump
    for (int i = 0; i < 1000; ++i)
    {
        lm::Vector2f nextPos = position;
        nextPos += speed * (1.f/120.f);
        speed.y -= 0.03f;
        if (map.indexAt(nextPos.x, nextPos.y))
        {
            float d = computeDepth(map, position);
            if (d > 0.f)
                position.y -= d;
            else
                position.y = -1.f;
            return position;
        }
        position = nextPos;
    }
    // Negative y indicates failure
    return {0, -1};
}

void
Bot::findPath(lm::GameObject& object)
{
    lm::GameObject* player = lm::GameObjectSet::instance().getObjectByTag("player");
    const Map& map = Level::instance().map();

    if (!player)
        return;

    if (lm::dist(player->position, object.position) > 1000.f)
        return;

    lm::Vector2f targetPos = { player->position.x, player->position.y };

    // The AI Script
    std::vector<TargetNode> nodes;
    std::list<TargetNode*> openNodes;
    std::list<TargetNode*> closedNodes;

    nodes.reserve(110);

    TargetNode rootNode;
    rootNode.position = { object.position.x, object.position.y };
    rootNode.type = Bot::TargetType::None;
    rootNode.parent = nullptr;

    nodes.push_back(rootNode);
    openNodes.push_back(&nodes.back());

    for (;;)
    {
        float score = 1.f / 0.f;
        TargetNode* best = nullptr;

        /* Consider than the target is unreachable once ~100 tiles have been scanned, or if no path exists */
        if (nodes.size() > 100 || openNodes.empty())
            return;
        for (auto targetNode : openNodes)
        {
            float nodeScore = pathLength(targetPos, *targetNode);
            if (nodeScore < score)
            {
                score = nodeScore;
                best = targetNode;
            }
        }

        if (lm::dist(best->position, targetPos) < 1.2f)
        {
            TargetNode* root = best;
            while (root->parent && root->parent->type != Bot::TargetType::None)
                root = root->parent;
            _target = root->position;
            _targetType = root->type;
            _targeting = true;
            std::cout << "FOUND MATCH ! SELF : " << best->position.x << " / " << best->position.y
                << " PLAYER : " << targetPos.x << " / " << targetPos.y << std::endl;
            _lastTargetDist = 10000.f;
            return;
        }

        // We found the best candidate for our research
        // Remove it from the open list and add it to the closed list
        openNodes.remove(best);
        closedNodes.push_back(best);

        // Now we populate the open list with possible nodes.
        TargetNode leftNode;
        leftNode.position = best->position - lm::Vector2f(0.25f, 0.0f);
        leftNode.type = Bot::TargetType::Walk;
        leftNode.parent = best;

        TargetNode rightNode;
        rightNode.position = best->position + lm::Vector2f(0.25f, 0.0f);
        rightNode.type = Bot::TargetType::Walk;
        rightNode.parent = best;

        TargetNode leftFall;
        float leftDepth = computeDepth(map, best->position + lm::Vector2f(-0.25f, 0.f));
        leftFall.position = best->position + lm::Vector2f(-1.0f, -leftDepth);
        leftFall.type = Bot::TargetType::Fall;
        leftFall.parent = best;

        TargetNode rightFall;
        float rightDepth = computeDepth(map, best->position + lm::Vector2f(0.25f, 0.f));
        rightFall.position = best->position + lm::Vector2f(1.0f, -rightDepth);
        rightFall.type = Bot::TargetType::Fall;
        rightFall.parent = best;

        TargetNode leftJump;
        leftJump.position = evaluateJump(map, best->position, {-6.f, 20.f});
        leftJump.type = Bot::TargetType::Jump;
        leftJump.parent = best;

        TargetNode rightJump;
        rightJump.position = evaluateJump(map, best->position, {6.f, 20.f});
        rightJump.type = Bot::TargetType::Jump;
        rightJump.parent = best;

        if (!map.indexAt(leftNode.position.x, leftNode.position.y + 0.5f)
            && map.indexAt(leftNode.position.x, leftNode.position.y - 0.5f)
            && !isNodeClosed(leftNode, closedNodes))
        {
            nodes.push_back(leftNode);
            openNodes.push_back(&nodes.back());
        }

        if (!map.indexAt(rightNode.position.x, rightNode.position.y + 0.5f)
            && map.indexAt(rightNode.position.x, rightNode.position.y - 0.5f)
            && !isNodeClosed(rightNode, closedNodes))
        {
            nodes.push_back(rightNode);
            openNodes.push_back(&nodes.back());
        }

        if (leftDepth > 0.5f && !isNodeClosed(leftFall, closedNodes))
        {
            nodes.push_back(leftFall);
            openNodes.push_back(&nodes.back());
            std::cout << leftFall.position.y << std::endl;
        }

        if (rightDepth > 0.5f && !isNodeClosed(rightFall, closedNodes))
        {
            nodes.push_back(rightFall);
            openNodes.push_back(&nodes.back());
        }

        if (leftJump.position.y > 0.f && !isNodeClosed(leftJump, closedNodes))
        {
            nodes.push_back(leftJump);
            openNodes.push_back(&nodes.back());
        }

        if (rightJump.position.y > 0.f && !isNodeClosed(rightJump, closedNodes))
        {
            nodes.push_back(rightJump);
            openNodes.push_back(&nodes.back());
        }

        std::cout << "DEPTH EVAL - left: " << leftDepth << " right: " << rightDepth << std::endl;
    }
}

