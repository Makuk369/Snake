#include <SDL3/SDL_main.h>
#include "headers/Game.hpp"

int main( int argc, char* args[] )
{
	Game game(800, 800);
	game.Run();

	return 0;
}
