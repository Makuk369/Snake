#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Vector2.hpp"
#include "AssetHandling.hpp"

class Snake
{
    public:
        Snake(SDL_Renderer* renderer, float posX, float posY);

        void Move(vector2 dir);

        void Render(SDL_Renderer* renderer);

    private:
        float mPosX;
        float mPosY;
        int mLength;

        SDL_Texture* mHead;
};