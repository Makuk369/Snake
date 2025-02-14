#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);