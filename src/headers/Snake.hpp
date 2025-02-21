#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameSettings.hpp"
#include "Structures.hpp"
#include "AssetHandling.hpp"

class Snake
{
    public:
        Snake(SDL_Renderer* renderer, float posX, float posY);
        ~Snake();

        void Move(Vector2 dir);
        void Render();
        bool CheckCollision();
        bool CheckCollisionWith(Vector2 otherPos);

    private:
        int mLength;

        // Index 0 is head
        std::vector<Vector2Rot> mBodyPositions;

        Texture mHeadTex;
        Texture mBodyTex;
        Texture mTailTex;
};