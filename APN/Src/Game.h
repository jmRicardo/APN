#pragma once

#include "SDL_mixer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>


class AssetManager;
class ColliderComponent;
class Menu;

class Game
{
public:
	Game();
	~Game();

	SDL_Cursor* nCursor;

	void init(const char* title, int width, int height, bool fullscreen);
	void loadGame();

	void menuInit();

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool menuRunning() { return menuIsRunning; }
	void render();
	void clean();
	void inicCursor();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Joystick* gGameController;
	
	static bool isRunning;
	static bool menuIsRunning;
	static int i;
	static SDL_Rect camera;
	static SDL_Rect viewPort;
	static AssetManager* assets;
	static Menu* menu;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupMenu,
		groupMenuButtons,
		groupEnemies
	};

private:

	int cnt = 0;
	SDL_Window *window;
};