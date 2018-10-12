
#include "DPGame.h"
#include <memory>
#undef main

int main()
{
	std::unique_ptr<DPGame> game = std::make_unique<DPGame>();

	//TO DO: exceptions
	try { game->setup("Dungeons of Pokemons",800, 600); }
	catch(...){return 0;}

	auto test = 0;
	while(game->isRunning())
	{
		//60 FPS
		SDL_Delay(1000. / 60.);

		//std::cout << SDL_GetError() << std::endl;
	

		game->handleEvents();
		game->update();
		game->draw();
	}


	return 0;
}