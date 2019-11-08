#pragma once

#include <string>
#include "SDL.h"

class Intro
{
public:

	Intro();
	~Intro();

	void init();
	void update();
	void draw();
	void play();



private:

	std::string number;
	SDL_Texture* letters;
	std::string path;
	int x, y, z, o;
	SDL_Texture* background;
	bool skipIntro;
	const int FPS = 25;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

};
