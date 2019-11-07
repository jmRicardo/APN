
#include "EnemiesManager.h"
#include <time.h>

extern Manager manager;

SpriteComponent sprite;


EnemiesManager::EnemiesManager()
{
	auto& enemy(manager.addEntity());
	auto& enemy2(manager.addEntity());
	auto& enemy3(manager.addEntity());
	auto& enemy4(manager.addEntity());
	auto& enemy5(manager.addEntity());



	enemy.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy.addComponent<ColliderComponent>("DGhost");
	enemy.addGroup(Game::groupEnemies);

	enemy2.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy2.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy2.addComponent<ColliderComponent>("DGhost");
	enemy2.addGroup(Game::groupEnemies);

	enemy3.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy3.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy3.addComponent<ColliderComponent>("DGhost");
	enemy3.addGroup(Game::groupEnemies);

	enemy4.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy4.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy4.addComponent<ColliderComponent>("DGhost");
	enemy4.addGroup(Game::groupEnemies);

	enemy5.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy5.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy5.addComponent<ColliderComponent>("DGhost");
	enemy5.addGroup(Game::groupEnemies);

	
	
}

auto& gEnemies(manager.getGroup(Game::groupEnemies));

void EnemiesManager::initEnemies(int e)
{
	srand(time(NULL));
	for (int y = 0; y < e; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			ePosition[y][x].x = rand() % 705 +1;
			ePosition[y][x].y = rand() % 598 +1;
		}	
		gEnemies[y]->getComponent<TransformComponent>().position = ePosition[y][0];
	}

	nEnemies = e;
	
	pos = -1;

}



void EnemiesManager::updatePosition(int time)
{
	x = 60 - time;

	if (x % 6 == 0 &&  time>0	&& timeChange !=time)
	{
		pos++;
		timeChange = time;
	}

		
	for (int x = 0; x < nEnemies; x++)
	{
		Vector2D gVelocity;
		Vector2D gPosition = gEnemies[x]->getComponent<TransformComponent>().position;

		

		if (ePosition[x][pos].x < ePosition[x][pos + 1].x)
		{
			gVelocity.x = 0.75;
			gEnemies[x]->getComponent<SpriteComponent>().Play("right");
		}
			
		else if (ePosition[x][pos].x > ePosition[x][pos + 1].x)
		{
			gVelocity.x = -0.75;
			gEnemies[x]->getComponent<SpriteComponent>().Play("left");
		}


		if (ePosition[x][pos].y < ePosition[x][pos + 1].y)
			gVelocity.y = 0.75;
		else if (ePosition[x][pos].y > ePosition[x][pos + 1].y)
			gVelocity.y = -0.75;

		if (gPosition.x > 700)
			gVelocity.x = -0.75;
		if( gPosition.x < 1)
			gVelocity.x = 0.75;
		if (gPosition.y > 590)
			gVelocity.y = -0.75;
		if( gPosition.y < 1)
			gVelocity.y = 0.75;

		gEnemies[x]->getComponent<TransformComponent>().velocity = gVelocity;

	}	

}
