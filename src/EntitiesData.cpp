#include "IEntity.hpp"

using namespace lm;

const EntityData gEntityData[] =
{
    {
        "Cross",
        ImageId::Cross,
        42,
        21,
        1.0,
        100,
        200,
        0,
        4,
        10,

        // Bounding box
        {
            {23, 48}, {25, 44}, {26, 26}, {25, 46}, {19, 48}
        },

        // Transitions
        {
            // Stand to ...
            {
                {0, 1, 1},
                {0, 1, 1},      // Run
                {0, 1, 1},      // Crouch
                {0, 1, 1},      // Jump
                {0, 1, 1}       // Secret
            },
            // Run to ...
            {
                {83, 13, 4},    // Stand
                {0, 1, 1},
                {0, 1, 1},      // Crouch
                {0, 1, 1},      // Jump
                {0, 1, 1}       // Secret
            },
            // Crouch to ...
            {
                {0, 1, 1},      // Stand
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1}
            },
            // Jump to ...
            {
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1}
            },
            // Secret to ...
            {
                {0, 1, 1},      // Stand
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1}
            },
        },

        // Animations
        {
            // Idle
            {0, 6, 13},
            // Run
            {6, 16, 6},
            // Crouch
            {22, 5, 10},
            // Jump
            {31, 19, 6},
            // Secret
            {0, 1}
        }
    }
};