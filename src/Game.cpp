#include "headers/Game.hpp"
#include "headers/GameSettings.hpp"
#include "headers/AssetHandling.hpp"
#include "headers/Timer.hpp"
#include "headers/Structures.hpp"
#include "headers/Snake.hpp"
#include "headers/Apple.hpp"

Game::Game()
	:mScreenWidth(SnakeSetings::gGridWidth * SnakeSetings::gGridScale), mScreenHeight(SnakeSetings::gGridHeight * SnakeSetings::gGridScale), mScore(0)
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
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

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

	Texture scoreNumTxtTex(renderer, "../assets/fonts/Roboto-Bold.ttf", 256);
	scoreNumTxtTex.LoadFromRenderedText(std::to_string(mScore), {0, 0, 0});
	scoreNumTxtTex.setColor(0, 0, 0, 32);
	float scoreNumTxtScale = SDL_min(2, mScreenWidth / scoreNumTxtTex.getWidth());

	Texture diedTxtTex(renderer, "../assets/fonts/Roboto-Bold.ttf", 64);
	diedTxtTex.LoadFromRenderedText("Snake Died!", {255, 0, 0});

	Texture scoreTxtTex(renderer, "../assets/fonts/Roboto-Bold.ttf", 64);
	scoreTxtTex.LoadFromRenderedText("SCORE:", {0, 0, 0});
	
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
						snakeMoveDir = {1, 0};
						apple.Respawn(snake.getPositions());
						mScore = 0;
						scoreNumTxtTex.LoadFromRenderedText(std::to_string(mScore));
						scoreNumTxtTex.setColor(0, 0, 0, 32);
						scoreNumTxtScale = SDL_min(2, mScreenWidth / scoreNumTxtTex.getWidth());
					}
					currentState = PLAYING;
				}
				if(event.key.key == SDLK_ESCAPE)
				{
					isRunning = false;
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
					scoreNumTxtTex.LoadFromRenderedText(std::to_string(mScore));
					scoreNumTxtTex.setColor(0, 0, 0, 32);
					scoreNumTxtScale = SDL_min(2, mScreenWidth / scoreNumTxtTex.getWidth());

					RandomBGColor();
				}

				moveDelay = 0;
			}

			
			//Clear screen
			SDL_RenderClear(renderer);
			
			scoreNumTxtTex.Render((mScreenWidth - scoreNumTxtTex.getWidth() * scoreNumTxtScale) / 2, (mScreenHeight - scoreNumTxtTex.getHeight() * scoreNumTxtScale) / 2, scoreNumTxtScale);
			apple.Render();
			snake.Render();

			//Update screen
			SDL_RenderPresent(renderer);
			break;

		case DEATH_MENU: // ------------------------------------------------------------------
			// Clear screen
			SDL_RenderClear(renderer);

			diedTxtTex.Render((mScreenWidth - diedTxtTex.getWidth()) / 2, (mScreenHeight - diedTxtTex.getHeight()) / 6);

			scoreTxtTex.Render((mScreenWidth - scoreTxtTex.getWidth()) / 2, (mScreenHeight - scoreTxtTex.getHeight()) / 3.5);

			scoreNumTxtTex.setColor(0, 0, 0, 255);
			scoreNumTxtTex.Render((mScreenWidth - scoreNumTxtTex.getWidth() * scoreNumTxtScale / 2) / 2, (mScreenHeight - scoreNumTxtTex.getHeight() * scoreNumTxtScale / 2) / 2, scoreNumTxtScale / 2);

			mainMenuTxtTex.setColor(0, 0, 0, 128);
			mainMenuTxtTex.Render((mScreenWidth - mainMenuTxtTex.getWidth()) / 2, (mScreenHeight - mainMenuTxtTex.getHeight()));

			//Update screen
			SDL_RenderPresent(renderer);
			break;
		
		default:
			break;
		}
	}
}

void Game::RandomBGColor()
{
	using namespace SnakeSetings;

	int rngI = SDL_rand(gBGColors.size());
	SDL_SetRenderDrawColor(renderer, gBGColors[rngI].r,  gBGColors[rngI].g,  gBGColors[rngI].b, 255);
}