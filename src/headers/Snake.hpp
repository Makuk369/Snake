#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameSettings.hpp"
#include "Vector2.hpp"
#include "AssetHandling.hpp"

class Snake
{
    public:
        Snake(SDL_Renderer* renderer, float posX, float posY);
        ~Snake();

        void Move(vector2 dir);
        void Render(SDL_Renderer* renderer);
        bool CheckCollision();

    private:
        float mPosX;
        float mPosY;
        int mLength;

        SDL_Texture* mHead;
};