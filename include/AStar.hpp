#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <list>
#include <vector>
#include <algorithm>
#include <Lums>

struct AStarNode
{
    AStarNode*      parent;
    lm::Vector2f    position;
    int             type;
    float           length;
};

class AStar
{
public:
    static const int maxNodes = 100;

    AStar(lm::Vector2f start, lm::Vector2f end)
    : _start(start)
    , _end(end)
    {
        _nodes.reserve(maxNodes);
        addOpenNode(nullptr, start, -1);
    }

    void
    addOpenNode(AStarNode* parent, lm::Vector2f position, int type, float lengthPenality = 0.f)
    {
        if (_nodes.size() >= maxNodes)
            return;
        for (auto node : _closed)
        {
            if (lm::dist(node->position, position) < 0.01f)
                return;
        }

        AStarNode node;
        node.parent = parent;
        node.position = position;
        node.type = type;
        node.length = parent ? parent->length + lm::dist(position, parent->position) : 0;
        node.length += lengthPenality;
        _nodes.push_back(node);
        _open.push_back(&(_nodes.back()));
    }

    template <typename Functor>
    bool
    getPath(AStarNode& node, Functor& functor)
    {
        for (;;)
        {
            if (_open.size() == 0 || _nodes.size() == maxNodes)
                return false;
            AStarNode* bestNode = *std::min_element(_open.begin(), _open.end(), [this](AStarNode* a, AStarNode* b)
            {
                return getLength(*a) < getLength(*b);
            });
            if (lm::dist(bestNode->position, _end) < 0.5f)
            {
                node = getFirstNode(*bestNode);
                return true;
            }
            functor(*this, *bestNode);
            closeNode(*bestNode);
        }
    }

private:
    float
    getLength(const AStarNode& node)
    {
        return node.length + lm::dist(node.position, _end);
    }

    AStarNode&
    getFirstNode(AStarNode& node)
    {
        AStarNode* iter = &node;
        while (iter->parent && iter->parent->parent)
            iter = iter->parent;
        return *iter;
    }

    void
    closeNode(AStarNode& node)
    {
        _closed.push_back(&node);
        _open.remove(&node);
    }

    lm::Vector2f            _start;
    lm::Vector2f            _end;
    std::vector<AStarNode>  _nodes;
    std::list<AStarNode*>   _open;
    std::list<AStarNode*>   _closed;
};

#endif
