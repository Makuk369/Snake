#include "headers/AssetHandling.hpp"

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path)
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
		else
		{
			SDL_SetTextureScaleMode(newTexture, SDL_SCALEMODE_NEAREST);
		}

		//Get rid of old loaded surface
		SDL_DestroySurface( loadedSurface );
	}

	return newTexture;
};

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string pathBase, std::string pathEnd)
{
	std::string path = pathBase + pathEnd;

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
		else
		{
			SDL_SetTextureScaleMode(newTexture, SDL_SCALEMODE_NEAREST);
		}

		//Get rid of old loaded surface
		SDL_DestroySurface( loadedSurface );
	}

	return newTexture;
};

// void DestroyTextures(std::array<SDL_Texture*, TEXTURES_COUNT>& textures)
// {
// 	for (SDL_Texture* texture : textures)
// 	{
// 		SDL_DestroyTexture(texture);
// 	}
// 	SDL_Log("Textures - destroyed!\n");
// };