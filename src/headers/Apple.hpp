#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameSettings.hpp"
#include "Structures.hpp"
#include "AssetHandling.hpp"

class Apple
{
    public:
        Apple(SDL_Renderer* renderer);
        ~Apple();

        void Respawn(const std::vector<Vector2Rot>& snakePositions);
        void Render();

        Vector2 getPosition();

    private:
        Vector2 mPosition;

        Texture mTex;
};