#include "headers/Snake.hpp"

Snake::Snake(SDL_Renderer* renderer, float posX, float posY)
{
    mPosX = posX * GRID_SCALE;
    mPosY = posY * GRID_SCALE;
    mLength = 3;
    mRotation = 0;

    mHead = LoadTexture(renderer, PATH_TO_IMGS, "snakeHead.png");

    SDL_Log("Snake - init!\n");
}

Snake::~Snake()
{
    SDL_DestroyTexture(mHead);
    SDL_Log("Snake - destroy!\n");
}

void Snake::Move(vector2 dir)
{
    mPosX += dir.x * GRID_SCALE;
    mPosY += dir.y * GRID_SCALE;

    if(dir.x == 1){ mRotation = 90; }
    if(dir.x == -1){ mRotation = -90; }
    if(dir.y == 1){ mRotation = 180; }
    if(dir.y == -1){ mRotation = 0; }
}

void Snake::Render(SDL_Renderer* renderer)
{
    SDL_FRect snakeRect = {mPosX, mPosY, 80, 80};
    // SDL_Log("Snake x,y = %.0f,%.0f\n", mPosX, mPosY);
    SDL_RenderTextureRotated(renderer, mHead, NULL, &snakeRect, mRotation, NULL, SDL_FLIP_NONE);
}

bool Snake::CheckCollision()
{
    // ----- Check playable area borders -----
    if(mPosX < 0)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }
    if(mPosY < 0)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }
    if(mPosX >= GRID_WIDTH * GRID_SCALE)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }
    if(mPosY >= GRID_HEIGHT * GRID_SCALE)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }

    return false;
}