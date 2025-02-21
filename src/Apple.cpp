#include "headers/Apple.hpp"

Apple::Apple(SDL_Renderer *renderer)
    :mPosition(), mIsEaten(false), mTex(renderer)
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

void Apple::GetEaten()
{
    mIsEaten = true;
    SDL_Log("Apple - eaten!\n");
}

void Apple::Respawn()
{
    SDL_rand(10);
}

void Apple::Render()
{
    if(!mIsEaten)
    {
        mTex.Render(mPosition.x, mPosition.y, GRID_SCALE / mTex.getWidth());
    }
}

Vector2 Apple::getPosition()
{
    return mPosition;
}