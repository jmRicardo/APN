

#include "ECS/TimerComponent.h"


extern Manager manager;

auto& label(manager.addEntity());

Timer::Timer(int xpos,int ypos, int count)
{
	
	seconds = count;
	elapsedTime = 0;
	startTimer(xpos, ypos,count);
	secondsLeft = count;
	starCounter = SDL_GetTicks();
}

void Timer::update()
{
	if (secondsLeft>0)
	{
		elapsedTime = (SDL_GetTicks() - starCounter ) / 1000;
		secondsLeft = seconds - elapsedTime;
		ss = std::to_string(secondsLeft);
		label.getComponent<UILabel>().SetLabelText(ss.c_str(), "commodore");
	}
}

int Timer::checkTime()
{
	return secondsLeft;
}


void Timer::startTimer(int x, int y, int count)
{
	label.addComponent<UILabel>(x, y, std::to_string(count) , "commodore", red);
}

void Timer::draw()
{
	label.draw();
}