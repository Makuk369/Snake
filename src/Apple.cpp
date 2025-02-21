#include "headers/Apple.hpp"

Apple::Apple(SDL_Renderer *renderer)
    :mPosition(), mTex(renderer)
{
    mTex.LoadFromFile("../assets/imgs/apple.png");
 
    SDL_srand(SDL_GetTicks());

    SDL_Log("Apple - init!\n");
}

Apple::~Apple()
{
    mTex.Free();

    SDL_Log("Apple - destroy!\n");
}

void Apple::Respawn(const std::vector<Vector2Rot>& snakePositions)
{
    Vector2 respawnPos;
    bool isFreePos = true;

    do
    {
        isFreePos = true;
        respawnPos = {(float)(SDL_rand(GRID_WIDTH) * GRID_SCALE), (float)(SDL_rand(GRID_HEIGHT) * GRID_SCALE)};
    
        // check if respawnPos is set on snake
        for (Vector2Rot snakePos : snakePositions)
        {
            if((respawnPos.x == snakePos.x) && (respawnPos.y == snakePos.y))
            {
                isFreePos = false;
                // SDL_Log("RespawnPos is on snake!\n");
            }
        }
    } while (!isFreePos);
    
    mPosition.x = respawnPos.x;
    mPosition.y = respawnPos.y;
}

void Apple::Render()
{
    mTex.Render(mPosition.x, mPosition.y, GRID_SCALE / mTex.getWidth());
}

Vector2 Apple::getPosition()
{
    return mPosition;
}