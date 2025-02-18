#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

//Texture wrapper class
class Texture
{
	public:
		Texture(SDL_Renderer* renderer);

		~Texture();

		//Loads image at specified path
		bool LoadFromFile(std::string path);
		
		//Creates image from font string
		bool LoadFromRenderedText(TTF_Font* font, std::string textureText, SDL_Color textColor);

		//Deallocates texture
		void Free();

		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		void setBlendMode(SDL_BlendMode blending);

		void setAlpha(Uint8 alpha);
		
		void Render(float x, float y, float scale = 1, SDL_FRect* clip = NULL, double angle = 0.0, SDL_FPoint* center = NULL, SDL_FlipMode flip = SDL_FLIP_NONE);

		float getWidth();
		float getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

        SDL_Renderer* mRenderer;

		//Image dimensions
		float mWidth;
		float mHeight;
};