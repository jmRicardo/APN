#pragma once

#include "SDL_mixer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
//#include <vector>
#include "Players.h"


class AssetManager;
class ColliderComponent;
class Menu;
class EnemiesManager;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void loadLevel();

	void scoreScreen();
	void setRandomPos();

	void finalScore();
	void menuLoad();

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool menuRunning() { return menuIsRunning; }
	void render();
	void clean();
	void inicCursor();
	void drawFog();
	void drawGameOver();
	void cleanFog();
	void stage(int x);
	
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static EnemiesManager* eManager;
	
	static bool isRunning;
	static bool menuIsRunning;
	static SDL_Rect camera;
	static SDL_Rect viewPort;
	static AssetManager* assets;
	static SDL_Texture* fogTex;

	static bool load;

	SDL_Cursor* nCursor;
	

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupMenu,
		groupMenuButtons,
		groupEnemies,
		groupLights
	};

private:
	int actualLevel;
	bool keyOne, keyTwo;
	bool pOneActive, pTwoActive;
	int cnt = 0;
	bool isGameOver;
	SDL_Window *window;
	SDL_Rect mouse;
	Player one;
	Player two;
};