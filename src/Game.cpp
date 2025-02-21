#include "headers/Game.hpp"

Game::Game()
	:mScreenWidth(GRID_WIDTH * GRID_SCALE), mScreenHeight(GRID_HEIGHT * GRID_SCALE), mScore(0)
{
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return;
	}

	if(!SDL_CreateWindowAndRenderer("Snake", mScreenWidth, mScreenHeight, 0, &window, &renderer))
	{
		SDL_Log( "Window and renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return;
	}
	//Enable vsync
	SDL_SetRenderVSync(renderer, 1);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white = 255, 255, 255, 255

	if(!TTF_Init())
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
	}

	mBigFont = TTF_OpenFont("../assets/fonts/Roboto-Bold.ttf", 64);
	if(mBigFont == NULL)
	{
		SDL_Log("Failed to load font! SDL_ttf Error: %s\n", SDL_GetError());
	}

	SDL_Log("Game - init!\n");
}
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	TTF_CloseFont(mBigFont);
	mBigFont = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
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

	Texture mainMenuTxtTex(renderer);
	mainMenuTxtTex.LoadFromRenderedText(mBigFont, "Press SPACE to START", {0, 0, 0});
	
	Snake snake(renderer, 5, 5);
	Vector2 snakeMoveDir = {1, 0};
	float moveDelay = 0;

	Apple apple(renderer);

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

			snake.Render();
			mainMenuTxtTex.Render((mScreenWidth - mainMenuTxtTex.getWidth()) / 2, (mScreenHeight - mainMenuTxtTex.getHeight()) / 4);

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case PLAYING: // -----------------------------
			moveDelay += deltaTime;

			if(moveDelay >= 0.5)
			{
				snake.Move(snakeMoveDir);

				if(snake.CheckCollision())
				{
					SDL_Log("Snake - died!\n");
					currentState = DEATH_MENU;
				}

				if(snake.CheckCollisionWith(apple.getPosition()))
				{
					apple.Respawn(snake.getPositions());
					mScore += 10;
				}

				moveDelay = 0;
			}

			
			//Clear screen
			SDL_RenderClear(renderer);
			
			apple.Render();
			snake.Render();

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case DEATH_MENU: // ---------------------------
			isRunning = false;
			break;
		
		default:
			break;
		}
	}
}