#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Game.h"

class Menu
{
public:
	Menu(Manager * man);
	~Menu();

	void init();
	void initNewGame();
	void update();
	void draw();
	void effect();
	

	static SDL_Rect mouseRect;
	static bool cursorActivo;
	


	
};