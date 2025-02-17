#include "headers/Snake.hpp"

Snake::Snake(SDL_Renderer* renderer, float posX, float posY)
{
    mLength = 3;

    mBodyPositions.resize(mLength);

    mBodyPositions[0] = {posX * GRID_SCALE, posY * GRID_SCALE, 0};

    mHeadTex = LoadTexture(renderer, PATH_TO_IMGS, "snakeHead.png");
    mBodyTex = LoadTexture(renderer, PATH_TO_IMGS, "snakeBody.png");
    mTailTex = LoadTexture(renderer, PATH_TO_IMGS, "snakeTail.png");

    SDL_Log("Snake - init!\n");
}

Snake::~Snake()
{
    SDL_DestroyTexture(mHeadTex);
    SDL_DestroyTexture(mBodyTex);
    SDL_DestroyTexture(mTailTex);
    SDL_Log("Snake - destroy!\n");
}

void Snake::Move(Vector2 dir)
{
    // SDL_Log("---------------------------\n");
    // Move snake body parts (exept head)
    for (int i = mLength-1; i >= 1; i--)
    {
        mBodyPositions[i] = mBodyPositions[i-1];
        // SDL_Log("Snake part %d pos = %.0f,%.0f\n", i, mBodyPositions[i].x, mBodyPositions[i].y);
    }

    // Move head
    mBodyPositions[0].x += dir.x * GRID_SCALE;
    mBodyPositions[0].y += dir.y * GRID_SCALE;

    if(dir.x == 1){ mBodyPositions[0].rotarion = 90; }
    if(dir.x == -1){ mBodyPositions[0].rotarion = -90; }
    if(dir.y == 1){ mBodyPositions[0].rotarion = 180; }
    if(dir.y == -1){ mBodyPositions[0].rotarion = 0; }
}

void Snake::Render(SDL_Renderer* renderer)
{
    SDL_Texture* snakePartTex = mHeadTex;

    for (int i = 0; i < mLength; i++)
    {
        if(i == mLength-1)
        {
            snakePartTex = mTailTex;
        }
        else if(i > 0)
        {
            snakePartTex = mBodyTex;
        }
        
        SDL_FRect snakeRect = {mBodyPositions[i].x, mBodyPositions[i].y, GRID_SCALE, GRID_SCALE};
        SDL_RenderTextureRotated(renderer, snakePartTex, NULL, &snakeRect, mBodyPositions[i].rotarion, NULL, SDL_FLIP_NONE);
    }
    
}

bool Snake::CheckCollision()
{
    // ----- Check playable area borders -----
    if(mBodyPositions[0].x < 0)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }
    if(mBodyPositions[0].y < 0)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }
    if(mBodyPositions[0].x >= GRID_WIDTH * GRID_SCALE)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }
    if(mBodyPositions[0].y >= GRID_HEIGHT * GRID_SCALE)
    {
        SDL_Log("Snake - died!\n");
        return true;
    }

    return false;
}