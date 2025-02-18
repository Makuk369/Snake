#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameSettings.hpp"
#include "AssetHandling.hpp"
#include "Timer.hpp"
#include "Structures.hpp"
#include "Snake.hpp"

class Game
{
    public:
        Game();
        ~Game();
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        void Run();
    
    private:
        int mScreenWidth;
        int mScreenHeight;

        enum GameState
        {
            MAIN_MENU,
            PLAYING,
            DEATH_MENU
        };
};
