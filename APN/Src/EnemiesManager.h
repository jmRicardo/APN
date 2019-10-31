#pragma once
#include "ECS/Components.h"


class EnemiesManager
{
public:	
	
	EnemiesManager();

	void initEnemies(int e);
	void updatePosition(int time);


private:

	Vector2D ePosition[5][10];
	int nEnemies;
	int pos;
	int x;
	int timeChange;
			

};