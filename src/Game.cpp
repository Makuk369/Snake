#include "headers/Game.hpp"
#include "headers/AssetHandling.hpp"
#include "headers/Timer.hpp"

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
	//Enable vsync
	SDL_SetRenderVSync(renderer, 1);
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

	// Load all textures, automaticly destroys them later
	Textures textures(renderer);

	Timer timer;
	timer.Start();

	// ---------- MAIN GAME LOOP ----------
	while(mIsRunning)
	{
		float deltaTime = timer.getDeltaTime();
		// SDL_Log("Delta time = %f\n", deltaTime);

		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_EVENT_QUIT)
			{
				mIsRunning = false;
			}
			else if(event.type == SDL_EVENT_KEY_DOWN)
			{
				if(event.key.key == SDLK_T)
				{
					SDL_Log("Time = %.3fs\n", timer.getTicks() / 1000.f);
				}
			}
		}

		//Clear screen
		SDL_RenderClear(renderer);

		SDL_RenderTexture(renderer, textures.apple, NULL, NULL);

		//Update screen
		SDL_RenderPresent(renderer);
	}
}