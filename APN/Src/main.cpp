#include "Game.h"
#include "Menu.h"

Game* game = nullptr;
Menu* menu = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	
	game = new Game();
	game->init("Aprobando Programacion", 1366, 768, false);

	menu = new Menu();
	menu->init();

	while (game->menuRunning() || game->running())
	{

		frameStart = SDL_GetTicks();

		if (game->menuRunning()) 
		{
			menu->update();
			menu->draw();
			if (!game->menuRunning())
			{
				game->loadGame();
			}
		}
		if (game->running())
		{
			game->handleEvents();
			game->update();
			game->render();
			if (!game->running())
			{
				SDL_RenderSetViewport(Game::renderer, NULL);
				menu->init();
			}
		}	

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}