#pragma once

#include "ECS/ECS.h"

class ScoreScreen
{
public:

	ScoreScreen(Manager* man);
	~ScoreScreen();

	void init();
	void update();
	void render();

	void scoreEffect(int score);

private:
	Manager* manager;

};