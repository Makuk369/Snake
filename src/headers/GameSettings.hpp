#pragma once
#include <SDL3/SDL_pixels.h> //for SDL_Color
#include <array>

namespace SnakeSetings
{
    // Default = 10, 10, 80
    const uint16_t gGridWidth = 10;
    const uint16_t gGridHeight = 10;
    const uint16_t gGridScale = 80;

    // Default = 2, 1, 10
    const uint8_t gGrowSize = 2;
    const float gMoveSpeedMultiplier = 1.0f;
    const uint16_t gScoreIncrease = 10;

    // First is white
    const std::array<SDL_Color, 9> gBGColors {{
        {255, 255, 255},
        {255, 173, 173},
        {255, 214, 165},
        {253, 255, 191},
        {202, 255, 191},
        {155, 246, 255},
        {160, 196, 255},
        {189, 178, 255},
        {255, 198, 255}
    }};
}
