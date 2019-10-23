
#include "ScoreScreen.h"
#include "ECS/Components.h"

ScoreScreen::ScoreScreen(Manager* man)
{
	manager = man;
}



void ScoreScreen::init()
{
	auto& scoreBack(manager->addEntity());
	auto& playerOne(manager->addEntity());
	auto& playerOneKeys(manager->addEntity());
	auto& playerOneScore(manager->addEntity());
	auto& playerTwo(manager->addEntity());
	auto& playerTwoKeys(manager->addEntity());
	auto& playerTwoScore(manager->addEntity());

	auto nextGame(manager->addEntity());


	
	scoreBack.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	scoreBack.addComponent<SpriteComponent>("menuBackgroundHD");
}

ScoreScreen::scoreEffect()
{

}