#include "headers/Game.hpp"

Game::Game()
{
	mScreenWidth = GRID_WIDTH * GRID_SCALE;
	mScreenHeight = GRID_HEIGHT * GRID_SCALE;

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
	// DestroyTextures(textures);

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
	bool isRunning = true;
	GameState currentState = MAIN_MENU;

	SDL_Event event;

	Timer timer;
	timer.Start();
	float deltaTime = 0;
	
	Snake snake(renderer, 5, 5);
	Vector2 snakeMoveDir = {1, 0};
	float moveDelay = 0;

	// ---------- MAIN GAME LOOP ----------
	while(isRunning)
	{
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_EVENT_QUIT)
			{
				isRunning = false;
			}
			else if(event.type == SDL_EVENT_KEY_DOWN)
			{
				// start the game
				if(event.key.key == SDLK_SPACE)
				{
					currentState = PLAYING;
				}
				// snake movement
				if(event.key.key == SDLK_W)
				{
					snakeMoveDir = {0, -1};
				}
				if(event.key.key == SDLK_A)
				{
					snakeMoveDir = {-1, 0};
				}
				if(event.key.key == SDLK_S)
				{
					snakeMoveDir = {0, 1};
				}
				if(event.key.key == SDLK_D)
				{
					snakeMoveDir = {1, 0};
				}
			}
		}

		deltaTime = timer.getDeltaTime();
		// SDL_Log("Delta time = %f\n", deltaTime);

		switch (currentState)
		{
		case MAIN_MENU: // ---------------------------
			//Clear screen
			SDL_RenderClear(renderer);

			snake.Render(renderer);

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case PLAYING: // -----------------------------
			moveDelay += deltaTime;

			if(moveDelay >= 0.5)
			{
				snake.Move(snakeMoveDir);
				moveDelay = 0;
			}
			if(snake.CheckCollision())
			{
				isRunning = false;
			}

			//Clear screen
			SDL_RenderClear(renderer);

			snake.Render(renderer);

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case DEATH_MENU: // ---------------------------
			
			break;
		
		default:
			break;
		}
	}
}