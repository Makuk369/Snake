#include "headers/Snake.hpp"

Snake::Snake(SDL_Renderer* renderer, float posX, float posY)
{
    mPosX = posX;
    mPosY = posY;
    mLength = 3;

    mHead = LoadTexture(renderer, PATH_TO_IMGS, "snakeHead.png");

    SDL_Log("Snake - init!\n");
};

void Snake::Move(vector2 dir)
{
    mPosX += dir.x * 80;
    mPosY += dir.y * 80;
};

void Snake::Render(SDL_Renderer* renderer)
{
    SDL_FRect snakeRect = {mPosX, mPosY, 80, 80};
    // SDL_RenderTexture(renderer, textures[SNAKE_HEAD], NULL, &snakeRect);
    SDL_RenderTexture(renderer, mHead, NULL, &snakeRect);
};