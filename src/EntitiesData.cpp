#include "IEntity.hpp"

using namespace lm;

const EntityData gEntityData[] =
{
    {
        "Yseult",
        ImageId::CommonBot,
        100,
        21,
        10,
        // Bounding box
        {
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}}
        },
        // Hitbox
        {
            {},
            {},
            {},
            {},
            {},
            {},
            {{0.5f, 1.5f}, {1.2f, 1.5f}},
            {}
        },
        // Animations
        {
            // Idle
            {91, 24, 4, true},
            // Run
            {115, 24, 2, true},
            // Crouch
            {22, 1, 10, true},
            // Jump
            {67, 12, 5, true},
            // Fall
            {67, 12, 5, true},
            // Dead
            {24, 43, 4, false},
            // Attack
            {0, 24, 2, false},
            // Hit
            {80, 12, 3, false}
        },
        // Speed
        {
            {0.0f, 0.0f},
            {0.5f, 0.0f},
            {0.0f, 0.0f},
            {0.5f, 1.0f},
            {0.5f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        },
        nullptr
    },
    {
        "Common Bot",
        ImageId::CommonBot,
        50,
        21,
        15,
        // Bounding box
        {
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}}
        },
        // Hitbox
        {
            {},
            {},
            {},
            {},
            {},
            {},
            {{0.5f, 1.5f}, {1.2f, 2.0f}},
            {}
        },
        // Animations
        {
            // Idle
            {91, 24, 4, true},
            // Run
            {115, 24, 2, true},
            // Crouch
            {22, 1, 10, true},
            // Jump
            {67, 12, 5, true},
            // Fall
            {67, 12, 5, true},
            // Dead
            {24, 43, 4, false},
            // Attack
            {0, 24, 2, false},
            // Hit
            {80, 12, 3, false}
        },
        // Speed
        {
            {0.0f, 0.0f},
            {0.4f, 0.0f},
            {0.0f, 0.0f},
            {0.4f, 0.9f},
            {0.4f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        },
        AI::basic
    },
    {
        "Boss",
        ImageId::CommonBoss,
        140,
        21,
        30,
        // Bounding box
        {
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}},
            {{1.4f,  0.23f}, {1.1f, 3.5f}}
        },
        // Hitbox
        {
            {},
            {},
            {},
            {},
            {},
            {},
            {{0.5f, 1.5f}, {1.2f, 2.0f}},
        },
        // Animations
        {
            // Idle
            {91, 24, 4, true},
            // Run
            {115, 24, 3, true},
            // Crouch
            {22, 1, 10, true},
            // Jump
            {67, 12, 5, true},
            // Fall
            {67, 12, 5, true},
            // Dead
            {24, 43, 4, false},
            // Attack
            {0, 24, 4, false},
            // Hit
            {80, 12, 6, false}
        },
        // Speed
        {
            {0.0f, 0.0f},
            {0.3f, 0.0f},
            {0.0f, 0.0f},
            {0.3f, 1.0f},
            {0.3f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        },
        AI::boss
    }
};