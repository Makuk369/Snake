#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Game
{
    public:
        Game(int screenWidth, int screenHeight);
        ~Game();
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        void Run();
    
    private:
        int mScreenWidth;
        int mScreenHeight;
        
        bool mIsRunning;
};
