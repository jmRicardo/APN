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
	void handleEvents();

	void newGameOption();
	

	static SDL_Rect mouseRect;

	Uint32 timerEfecto;
	bool activar;


	enum menuOptions {

		Start,
		Continue,
		NewGame,
		Options,
		Credits,
		Highscore,
		Quit
	};
	
private:
	int setOption;

	std::string playerOneName = "";
	std::string playerTwoName = "";
	bool playerOneEdit = false;
	bool playerTwoEdit = false;
	Uint32 mouseButton;
	bool cursorActivo;
	Uint32 stamp;
	bool menuHasChanged;
	bool adminModeActive;


	
};