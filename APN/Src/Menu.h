#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Game.h"
#include <windows.h>
#include "ScorePlayer.h"


class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void initNewGame();
	void initStart();
	void initOptions();
	void initCredits();
	void initHScore();

	void update();
	void draw();
	void effect();
	void handleEvents();

	void createAdminProcess(LPSTR path);

	void click();
	
	void newGameOption();

	static std::string pOneName;
	static std::string pTwoName;
	static SDL_Rect mouseRect;
	static char pOneCHar[20];
	static char pTwoCHar[20];

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


	bool playerOneEdit = false;
	bool playerTwoEdit = false;
	Uint32 mouseButton;
	bool cursorActivo;
	Uint32 stamp;
	bool menuHasChanged;
	bool adminModeActive;
	bool mineModeActive;


	
};