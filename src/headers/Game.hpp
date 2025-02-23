#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "GameSettings.hpp"
#include "AssetHandling.hpp"
#include "Timer.hpp"
#include "Structures.hpp"
#include "Snake.hpp"
#include "Apple.hpp"

class Game
{
    public:
        Game();
        ~Game();
        
        void Run();
        
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        int mScreenWidth;
        int mScreenHeight;
        int mScore;

        enum GameState
        {
            MAIN_MENU,
            PLAYING,
            DEATH_MENU
        };
};
