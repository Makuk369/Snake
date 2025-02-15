#include "headers/Game.hpp"
#include "headers/AssetHandling.hpp"
#include "headers/Timer.hpp"
#include "headers/Vector2.hpp"
#include "headers/Snake.hpp"

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
	// DestroyTextures(textures);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	SDL_Log("Game - quit!\n");
}

// void Snake::Render(SDL_Renderer* renderer)
// {
//     SDL_FRect snakeRect = {mPosX, mPosY, 80, 80};
//     SDL_RenderTexture(renderer, textures[SNAKE_HEAD], NULL, &snakeRect);
// };

void Game::Run()
{
	SDL_Log("Game - running!\n");
	mIsRunning = true;

	SDL_Event event;

	// textures[SNAKE_HEAD] = LoadTexture(renderer, PATH_TO_IMGS, "snakeHead.png");

	Timer timer;
	timer.Start();

	Snake snake(renderer, 0, 0);

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
				// if(event.key.key == SDLK_W)
				// {
				// 	snakePosY -= 80;
				// }
				// if(event.key.key == SDLK_A)
				// {
				// 	snakePosX -= 80;
				// }
				// if(event.key.key == SDLK_S)
				// {
				// 	snakePosY += 80;
				// }
				// if(event.key.key == SDLK_D)
				// {
				// 	snakePosX += 80;
				// }
				if(event.key.key == SDLK_SPACE)
				{
					snake.Move({1, 0});
				}
			}
		}

		//Clear screen
		SDL_RenderClear(renderer);

		snake.Render(renderer);
		// SDL_FRect snakeRect = {0, 0, 80, 80};
		// SDL_RenderTexture(renderer, textures[SNAKE_HEAD], NULL, &snakeRect);

		//Update screen
		SDL_RenderPresent(renderer);
	}
}