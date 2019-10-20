

#include "EnemiesManager.h"

#include "ECS/Components.h"

extern Manager manager;

auto& enemy(manager.addEntity());
auto& enemy2(manager.addEntity());
auto& enemy3(manager.addEntity());
auto& enemy4(manager.addEntity());
auto& enemy5(manager.addEntity());

EnemiesManager::EnemiesManager()
{
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
}


void EnemiesManager::checkDifficulty(int level)
{
	enemies = level;
}

void EnemiesManager::initPosition()
{

}


void EnemiesManager::init(int level)
{
	checkDifficulty(level);



}


