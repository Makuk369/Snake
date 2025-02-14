#include "headers/AssetHandling.hpp"

Textures::Textures(SDL_Renderer* renderer)
{
    mImgsPath = "../assets/imgs/";

    snakeHead = LoadTexture(renderer, std::string(mImgsPath).append("sniper.png"));
    snakeBody = LoadTexture(renderer, std::string(mImgsPath).append("sniper.png"));
    snakeTail = LoadTexture(renderer, std::string(mImgsPath).append("sniper.png"));
    apple = LoadTexture(renderer, std::string(mImgsPath).append("sniper.png"));

    SDL_Log("Textures - loaded!\n");
};

Textures::~Textures()
{
    SDL_DestroyTexture(snakeHead);
	snakeHead = NULL;
	SDL_DestroyTexture(snakeBody);
	snakeBody = NULL;
    SDL_DestroyTexture(snakeTail);
	snakeTail = NULL;
    SDL_DestroyTexture(apple);
	apple = NULL;

    SDL_Log("Textures - destroyed!\n");
};

SDL_Texture* Textures::LoadTexture(SDL_Renderer* renderer, std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == NULL )
		{
			SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_DestroySurface( loadedSurface );
	}

	return newTexture;
};