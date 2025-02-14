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

	if(!SDL_CreateWindowAndRenderer("Snake", mScreenWidth, mScreenHeight, 0, &mWindow, &mRenderer))
	{
		SDL_Log( "Window and renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return;
	}
	SDL_Log("SDL_CreateWindowAndRenderer - success!\n");

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // white = 255, 255, 255, 255
}
Game::~Game()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	SDL_Log("Game - quit\n");
}

void Game::Run()
{
	SDL_Log("Game - running!\n");
	mIsRunning = true;

	SDL_Event event;

	SDL_Texture* testTexture = LoadTexture(mRenderer, "../assets/imgs/sniper.png");

	// ---------- MAIN GAME LOOP ----------
	while(mIsRunning)
	{
		// SDL_Delay(5000);

		while(SDL_PollEvent(&event) != 0)
		{
			if( event.type == SDL_EVENT_QUIT )
			{
				mIsRunning = false;
			}
		}

		//Clear screen
		SDL_RenderClear(mRenderer);

		SDL_RenderTexture(mRenderer, testTexture, NULL, NULL);

		//Update screen
		SDL_RenderPresent(mRenderer);
	}

	//Free loaded image
	SDL_DestroyTexture(testTexture);
	testTexture = NULL;
}