#include "headers/Game.hpp"
#include <iostream>

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

	SDL_Log("Game - init!\n");
}
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

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

	Texture mainMenuTxtTex(renderer, "../assets/fonts/Roboto-Bold.ttf", 64);
	mainMenuTxtTex.LoadFromRenderedText("Press SPACE to START", {0, 0, 0});

	Texture scoreTxtTex(renderer, "../assets/fonts/Roboto-Bold.ttf", 256);
	scoreTxtTex.LoadFromRenderedText(std::to_string(mScore), {0, 0, 0});
	scoreTxtTex.setColor(0, 0, 0, 32);
	float scoreTxtScale = SDL_min(2, mScreenWidth / scoreTxtTex.getWidth());
	
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
					// Reset
					if(currentState == DEATH_MENU) 
					{
						snake.Reset(5, 5);
						apple.Respawn(snake.getPositions());
						scoreTxtTex.setColor(0, 0, 0, 32);
						scoreTxtScale = SDL_min(2, mScreenWidth / scoreTxtTex.getWidth());
						mScore = 0;
					}
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
		case MAIN_MENU: // --------------------------------------------------------------
			//Clear screen
			SDL_RenderClear(renderer);

			snake.Render();
			mainMenuTxtTex.Render((mScreenWidth - mainMenuTxtTex.getWidth()) / 2, (mScreenHeight - mainMenuTxtTex.getHeight()) / 4);

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case PLAYING: // ------------------------------------------------------------------
			moveDelay += deltaTime;
			if(moveDelay >= 0.5)
			{
				snake.Move(snakeMoveDir);

				// ded
				if(snake.CheckCollision())
				{
					SDL_Log("Snake - died!\n");
					currentState = DEATH_MENU;
					break;
				}

				// eat apple
				if(snake.CheckCollisionWith(apple.getPosition()))
				{
					apple.Respawn(snake.getPositions());
					snake.Grow(2);

					mScore += 10;
					scoreTxtTex.LoadFromRenderedText(std::to_string(mScore));
					scoreTxtTex.setColor(0, 0, 0, 32);
					scoreTxtScale = SDL_min(2, mScreenWidth / scoreTxtTex.getWidth());
				}

				moveDelay = 0;
			}

			
			//Clear screen
			SDL_RenderClear(renderer);
			
			scoreTxtTex.Render((mScreenWidth - scoreTxtTex.getWidth() * scoreTxtScale) / 2, (mScreenHeight - scoreTxtTex.getHeight() * scoreTxtScale) / 2, scoreTxtScale);
			apple.Render();
			snake.Render();

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case DEATH_MENU: // ------------------------------------------------------------------
			// Clear screen
			SDL_RenderClear(renderer);

			mainMenuTxtTex.LoadFromRenderedText("Snake Died!", {255, 0, 0});
			mainMenuTxtTex.Render((mScreenWidth - mainMenuTxtTex.getWidth()) / 2, (mScreenHeight - mainMenuTxtTex.getHeight()) / 6);

			mainMenuTxtTex.LoadFromRenderedText("SCORE:", {0, 0, 0});
			mainMenuTxtTex.Render((mScreenWidth - mainMenuTxtTex.getWidth()) / 2, (mScreenHeight - mainMenuTxtTex.getHeight()) / 3.5);

			scoreTxtTex.setColor(0, 0, 0, 255);
			scoreTxtTex.Render((mScreenWidth - scoreTxtTex.getWidth() * scoreTxtScale / 2) / 2, (mScreenHeight - scoreTxtTex.getHeight() * scoreTxtScale / 2) / 2, scoreTxtScale / 2);

			//Update screen
			SDL_RenderPresent(renderer);
			break;
		
		default:
			break;
		}
	}
}