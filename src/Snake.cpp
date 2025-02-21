#include "headers/Snake.hpp"

Snake::Snake(SDL_Renderer* renderer, float posX, float posY)
    :mLength(3), mHeadTex(renderer), mBodyTex(renderer)
{
    mBodyPositions.resize(mLength);

    mBodyPositions[0] = {posX * GRID_SCALE, posY * GRID_SCALE, 90};
    mBodyPositions[1] = {(posX-1) * GRID_SCALE, posY * GRID_SCALE, 90};
    mBodyPositions[2] = {(posX-2) * GRID_SCALE, posY * GRID_SCALE, 90};

    mHeadTex.LoadFromFile("../assets/imgs/snakeHead.png");
    mBodyTex.LoadFromFile("../assets/imgs/snakeBody.png");

    SDL_Log("Snake - init!\n");
}

Snake::~Snake()
{
    mHeadTex.Free();
    mBodyTex.Free();
    SDL_Log("Snake - destroy!\n");
}

void Snake::Move(Vector2 dir)
{
    // Move snake body parts (exept head)
    for (int i = mLength-1; i >= 1; i--)
    {
        mBodyPositions[i] = mBodyPositions[i-1];
    }

    // Move head
    mBodyPositions[0].x += dir.x * GRID_SCALE;
    mBodyPositions[0].y += dir.y * GRID_SCALE;

    if(dir.x == 1){ mBodyPositions[0].rotarion = 90; }
    if(dir.x == -1){ mBodyPositions[0].rotarion = -90; }
    if(dir.y == 1){ mBodyPositions[0].rotarion = 180; }
    if(dir.y == -1){ mBodyPositions[0].rotarion = 0; }
}

void Snake::Grow(int growSize)
{
    mLength += growSize;

    mBodyPositions.resize(mLength, mBodyPositions[mLength-growSize-1]);
}

void Snake::Render()
{
    Texture* snakePartTex = &mHeadTex;

    Uint8 colorDarken = 50 / mLength;
    Uint8 currentR = 125;
    Uint8 currentG = 180;
    Uint8 currentB = 65;

    for (int i = 0; i < mLength; i++)
    {
        if(i > 0)
        {
            snakePartTex = &mBodyTex;

            currentR -= colorDarken;
            currentG -= colorDarken;
            currentB -= colorDarken;
            snakePartTex->setColor(currentR, currentG, currentB);
        }

        snakePartTex->Render(mBodyPositions[i].x, mBodyPositions[i].y, GRID_SCALE / snakePartTex->getWidth(), NULL, mBodyPositions[i].rotarion, NULL);
    }
}

bool Snake::CheckCollision()
{
    // ----- Check playable area borders -----
    if(mBodyPositions[0].x < 0)
    {
        return true;
    }
    if(mBodyPositions[0].y < 0)
    {
        return true;
    }
    if(mBodyPositions[0].x >= GRID_WIDTH * GRID_SCALE)
    {
        return true;
    }
    if(mBodyPositions[0].y >= GRID_HEIGHT * GRID_SCALE)
    {
        return true;
    }

    // ----- Check if head on body part -----
    for (size_t i = 1; i < mLength; i++)
    {
        if((mBodyPositions[0].x == mBodyPositions[i].x) && (mBodyPositions[0].y == mBodyPositions[i].y))
        {
            return true;
        }
    }

    return false;
}

bool Snake::CheckCollisionWith(Vector2 otherPos)
{
    if((mBodyPositions[0].x == otherPos.x) && (mBodyPositions[0].y == otherPos.y))
    {
        return true;
    }

    return false;
}

std::vector<Vector2Rot> Snake::getPositions()
{
    return mBodyPositions;
}