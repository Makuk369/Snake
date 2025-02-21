#pragma once
#include <SDL3/SDL.h>
#include "GameSettings.hpp"
#include "Structures.hpp"
#include "AssetHandling.hpp"

class Apple
{
    public:
        Apple(SDL_Renderer* renderer);
        ~Apple();

        void GetEaten();
        void Respawn();
        void Render();

        Vector2 getPosition();

    private:
        Vector2 mPosition;

        bool mIsEaten;

        Texture mTex;
};