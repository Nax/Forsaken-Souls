#include "IEntity.hpp"
#include "Assets.hpp"

using namespace lm;

const EntityData gEntityData[] =
{
    {
        "Yseult",
        Assets::Texture::Yseult,
        100,
        21,
        10,
        // Bounding box
        {
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}},
            {{4.3f,  0.23f}, {1.4f, 3.0f}}
        },
        // Hitbox
        {
            {},
            {},
            {},
            {},
            {},
            {},
            {{{0.5f, 1.2f}, {3.4f, 2.0f}}, 9, 7},
            {}
        },
        // Animations
        {
            // Idle
            {17, 1, 4, true},
            // Run
            {18, 19, 4, true},
            // Crouch
            {22, 1, 10, true},
            // Jump
            {37, 1, 5, true},
            // Fall
            {37, 1, 5, true},
            // Dead
            {24, 1, 30, false},
            // Attack
            {0, 16, 3, false},
            // Hit
            {24, 1, 40, false}
        },
        // Speed
        {
            {0.0f, 0.0f},
            {0.7f, 0.0f},
            {0.0f, 0.0f},
            {0.7f, 1.0f},
            {0.7f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        },
        nullptr
    },
    {
        "Common Bot",
        Assets::Texture::Yseult,
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
            {{{0.5f, 1.5f}, {1.2f, 2.0f}}, 13, 6},
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
        Assets::Texture::Yseult,
        140,
        21,
        30,
        // Bounding box
        {
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}},
            {{3.f,  0.23f}, {2.f, 4.f}}
        },
        // Hitbox
        {
            {},
            {},
            {},
            {},
            {},
            {},
            {{{0.f, 1.0f}, {3.f, 1.5f}}, 10, 26},
        },
        // Animations
        {
            // Idle
            {59, 24, 4, true},
            // Run
            {106, 24, 3, true},
            // Crouch
            {105, 24, 10, true},
            // Jump
            {67, 12, 5, true},
            // Fall
            {67, 12, 5, true},
            // Dead
            {130, 33, 4, false},
            // Attack
            {0, 42, 4, false},
            // Hit
            {42, 17, 4, false}
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