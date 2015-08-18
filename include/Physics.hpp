#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <Lums>
#include "Map.hpp"

namespace Physics
{
    static const float gravity = 0.3f;

    bool    intersect(const Map& map, lm::Rect2f boundingBox);
    void    computeNextFrame(const Map& map, lm::Rect2f& boundingBox, lm::Vector2f& speed, bool& grounded);
    bool    computeFinalPosition(lm::Vector2f& output, int& frames, const Map& map, lm::Rect2f boundingBox, lm::Vector2f speed);
}

#endif
