#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Textures
{
private:
    std::string mImgsPath;

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
    
public:
    Textures(SDL_Renderer* renderer);
    ~Textures();

    SDL_Texture* snakeHead;
    SDL_Texture* snakeBody;
    SDL_Texture* snakeTail;
    SDL_Texture* apple;
};