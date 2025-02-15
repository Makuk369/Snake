#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <unordered_map>

#define PATH_TO_IMGS std::string("../assets/imgs/")

// enum TextureID
// {
//     SNAKE_HEAD,
// };

// static std::unordered_map<TextureID, SDL_Texture*> textures;

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string pathBase, std::string pathEnd);

// void DestroyTextures(std::unordered_map<TextureID, SDL_Texture*>& textures);