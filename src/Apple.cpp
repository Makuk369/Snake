#include "headers/Apple.hpp"
#include "headers/GameSettings.hpp"

Apple::Apple(SDL_Renderer *renderer)
    :mPosition({5 * SnakeSetings::gGridScale, 3 * SnakeSetings::gGridScale}), mTex(renderer)
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
        respawnPos = {(float)(SDL_rand(SnakeSetings::gGridWidth) * SnakeSetings::gGridScale), (float)(SDL_rand(SnakeSetings::gGridWidth) * SnakeSetings::gGridScale)};
    
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
    mTex.Render(mPosition.x, mPosition.y, SnakeSetings::gGridScale / mTex.getWidth());
}

Vector2 Apple::getPosition()
{
    return mPosition;
}