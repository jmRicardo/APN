
#include "EnemiesManager.h"
#include <time.h>

extern Manager manager;


EnemiesManager::EnemiesManager()
{
	auto& enemy(manager.addEntity());
	auto& enemy2(manager.addEntity());
	auto& enemy3(manager.addEntity());
	auto& enemy4(manager.addEntity());
	auto& enemy5(manager.addEntity());

	enemy.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy.addGroup(Game::groupEnemies);

	enemy2.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy2.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy2.addGroup(Game::groupEnemies);

	enemy3.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy3.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy3.addGroup(Game::groupEnemies);

	enemy4.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy4.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy4.addGroup(Game::groupEnemies);

	enemy5.addComponent<TransformComponent>(0, 0, 95, 42, 1);
	enemy5.addComponent<SpriteComponent>("DGhost", true, true, true);
	enemy5.addGroup(Game::groupEnemies);

	
	srand(time(NULL));
}

auto& gEnemies(manager.getGroup(Game::groupEnemies));

void EnemiesManager::initEnemies(int e)
{
	for (int y = 0; y < e; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			enemies[y][x].x = rand() % 800;
			enemies[y][x].y = rand() % 640;
		}
	

		gEnemies[y]->getComponent<TransformComponent>().position = enemies[y][0];
	}

	nEnemies = e;
	
	pos = -1;

}

int timeChange;

void EnemiesManager::updatePosition(int time)
{
	x = 60 - time;

	if (x % 6 == 0 &&  time>0	&& timeChange !=time)
	{
		pos++;
		timeChange = time;
	}

	std::cout << pos << std::endl;

	
	for (int x = 0; x < nEnemies; x++)
	{
		Vector2D gVelocity;
		
		if (enemies[x][pos].x < enemies[x][pos + 1].x)
			gVelocity.x = 1;
		else if (enemies[x][pos].x > enemies[x][pos + 1].x)
			gVelocity.x = -1;
		else
			gVelocity.x = 0;

		if (enemies[x][pos].y < enemies[x][pos + 1].y)
			gVelocity.y = 1;
		else if (enemies[x][pos].y > enemies[x][pos + 1].y)
			gVelocity.y = -1;
		else
			gVelocity.y = 0;

		gEnemies[x]->getComponent<TransformComponent>().velocity = gVelocity;

	}	

}
