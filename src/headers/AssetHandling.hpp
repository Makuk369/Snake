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
		Texture(SDL_Renderer* renderer, std::string pathToFont, Uint16 fontSize);

		// Complete dealocation
		~Texture();

		// Loads image at specified path
		bool LoadFromFile(std::string path);
		
		// Creates image from string if passed string is different from current
		// Default color = white
		bool LoadFromRenderedText(const std::string& setText, SDL_Color textColor = {255, 255, 255, 255});

		//Partial dealocation for repeated loading
		void Free();

		void Render(float x, float y, float scale = 1, SDL_FRect* clip = NULL, double angle = 0.0, SDL_FPoint* center = NULL, SDL_FlipMode flip = SDL_FLIP_NONE);
		
		// R, G, B, A
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

		void setBlendMode(SDL_BlendMode blending);

		float getWidth();
		float getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

        SDL_Renderer* mRenderer;

		// Used if its texture from text
		TTF_Font* mFont;
		std::string mText;

		//Image dimensions
		float mWidth;
		float mHeight;
};