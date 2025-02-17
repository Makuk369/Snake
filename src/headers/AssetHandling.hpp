#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#define PATH_TO_IMGS std::string("../assets/imgs/")

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string pathBase, std::string pathEnd);

// void DestroyTextures();