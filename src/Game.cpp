#include "headers/Game.hpp"
#include "headers/AssetHandling.hpp"

Game::Game(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return;
	}
	SDL_Log("SDL_Init - success!\n");

	if(!SDL_CreateWindowAndRenderer("Snake", mScreenWidth, mScreenHeight, 0, &window, &renderer))
	{
		SDL_Log( "Window and renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return;
	}
	SDL_Log("SDL_CreateWindowAndRenderer - success!\n");

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white = 255, 255, 255, 255
}
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	SDL_Log("Game - quit!\n");
}

void Game::Run()
{
	SDL_Log("Game - running!\n");
	mIsRunning = true;

	SDL_Event event;

	// Load all textures
	Textures textures(renderer);

	// ---------- MAIN GAME LOOP ----------
	while(mIsRunning)
	{
		while(SDL_PollEvent(&event) != 0)
		{
			if( event.type == SDL_EVENT_QUIT )
			{
				mIsRunning = false;
			}
		}

		//Clear screen
		SDL_RenderClear(renderer);

		SDL_RenderTexture(renderer, textures.apple, NULL, NULL);

		//Update screen
		SDL_RenderPresent(renderer);
	}
}