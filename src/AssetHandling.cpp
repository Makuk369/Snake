#include "headers/AssetHandling.hpp"
#include <iostream>

Texture::Texture(SDL_Renderer* renderer)
	: mTexture(NULL), mRenderer(renderer), mWidth(0), mHeight(0), mFont(NULL), mText("")
{}

Texture::Texture(SDL_Renderer* renderer, std::string pathToFont, Uint16 fontSize)
	: mTexture(NULL), mRenderer(renderer), mWidth(0), mHeight(0), mFont(NULL), mText("")
{
	mFont = TTF_OpenFont(pathToFont.c_str(), fontSize);
	if(mFont == NULL)
	{
		SDL_Log("Failed to load font! SDL_ttf Error: %s\n", SDL_GetError());
	}
}

Texture::~Texture()
{
	Free();

	mRenderer = NULL;

	if(mFont != NULL)
	{
		TTF_CloseFont(mFont);
		mFont = NULL;
		mText.clear();
	}
}

bool Texture::LoadFromFile(std::string path)
{
	Free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if( mTexture == NULL )
		{
			SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);

			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_DestroySurface( loadedSurface );
	}

	//Return success
	return mTexture != NULL;
}

bool Texture::LoadFromRenderedText(const std::string& setText, SDL_Color textColor)
{
	if(mText.compare(setText) == 0)
	{
		// SDL_Log("Trying to load a text texture with the same text: %s == %s", mText, setText);
		return true;
	}
	else
	{
		mText = setText;
	}

	//Get rid of preexisting texture
	Free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, setText.c_str(), 0, textColor);
	if(textSurface == NULL)
	{
		SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if(mTexture == NULL)
		{
			SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_DestroySurface(textSurface);
	}
	
	//Return success
	return mTexture != NULL;
}

void Texture::Free()
{
	//Free texture if it exists
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::Render(float x, float y, float scale, SDL_FRect* clip, double angle, SDL_FPoint* center, SDL_FlipMode flip)
{
	//Set rendering space and render to screen
	SDL_FRect renderQuad = {x, y, mWidth * scale, mHeight * scale};

	//Set clip rendering dimensions
	if(clip != NULL)
	{
		renderQuad.w = clip->w * scale;
		renderQuad.h = clip->h * scale;
	}

	//Render to screen
	SDL_RenderTextureRotated(mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

float Texture::getWidth()
{
	return mWidth;
}

float Texture::getHeight()
{
	return mHeight;
}
