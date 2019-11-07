#pragma once

#include "Components.h"
#include <sstream>


class Timer : public Component
{
public:

	std::string ss;
	SDL_Color red = {255,0,0,200};

	Timer(int xpos, int ypos, int count);

	void update() override;	
	void draw() override;
	int checkTime();
	void startTimer(int x, int y,int count);
	void setTimer(int count);

private:

	int seconds;
	int elapsedTime;
	int secondsLeft;
	int starCounter;
};
