#include "Menu.h"
#include "ECS\Components.h"
#include "Collision.h"

Manager* manager;

SDL_Rect Menu::mouseRect;


Menu::Menu(Manager* man) 
{
	manager = man;
	setOption = Start;
	cursorActivo = false;
}

Menu::~Menu()
{}

auto& menuBack(manager->addEntity());
auto& logo(manager->addEntity());
auto& logoS(manager->addEntity());
auto& logo2(manager->addEntity());
auto& logo2S(manager->addEntity());
auto& option1(manager->addEntity());
auto& option2(manager->addEntity());
auto& option3(manager->addEntity());
auto& option4(manager->addEntity());
auto& option5(manager->addEntity());
auto& quit(manager->addEntity());
auto& menuCursor(manager->addEntity());

auto& adminMode(manager->addEntity());

SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 155, 0, 0, 50 };
SDL_Color grey = { 110, 110,110, 255 };


void Menu::init()
{
	setOption = Start;

	menuBack.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	menuBack.addComponent<SpriteComponent>("menuBackgroundHD");
	menuBack.addGroup(Game::groupMenu);


	logoS.addComponent<UILabel>(482, 137, "A programmer's", "pixel", black);
	logoS.addGroup(Game::groupMenu);
	logo2S.addComponent<UILabel>(482, 177, "NIGHTMARE!", "pixelBig", black);
	logo2S.addGroup(Game::groupMenu);

	logo.addComponent<UILabel>(480, 135, "A programmer's", "pixel", white);
	logo.addGroup(Game::groupMenu);
	logo2.addComponent<UILabel>(480, 175, "NIGHTMARE!", "pixelBig", white);
	logo2.addGroup(Game::groupMenu);
	
	option1.addComponent<UILabel>(650, 400, "CONTINUE", "commodore", white);
	option1.addComponent<TransformComponent>(650, 400, 60, 350, 1);
	option1.addComponent<ColliderComponent>("menuCursor");
	option1.addGroup(Game::groupMenuButtons);

	option2.addComponent<UILabel>(650, 465, "NEW GAME", "commodore", white);
	option2.addComponent<TransformComponent>(650, 465, 60, 350, 1);
	option2.addComponent<ColliderComponent>("menuCursor");
	option2.addGroup(Game::groupMenuButtons);

	option3.addComponent<UILabel>(650, 530, "OPTIONS", "commodore", white);
	option3.addComponent<TransformComponent>(650, 530, 60, 350, 1);
	option3.addComponent<ColliderComponent>("menuCursor");
	option3.addGroup(Game::groupMenuButtons);

	option4.addComponent<UILabel>(650, 595, "CREDITS", "commodore", white);
	option4.addComponent<TransformComponent>(650, 595, 60, 350, 1);
	option4.addComponent<ColliderComponent>("menuCursor");
	option4.addGroup(Game::groupMenuButtons);

	option5.addComponent<UILabel>(650, 660, "HIGH SCORE", "commodore", white);
	option5.addComponent<TransformComponent>(650, 660, 60, 350, 1);
	option5.addComponent<ColliderComponent>("menuCursor");
	option5.addGroup(Game::groupMenuButtons);

	quit.addComponent<UILabel>(650, 725, "QUIT", "commodore", white);
	quit.addComponent<TransformComponent>(650, 725, 60, 350, 1);
	quit.addComponent<ColliderComponent>("menuCursor");
	quit.addGroup(Game::groupMenuButtons);

	menuCursor.addComponent<TransformComponent>(0,0,70,450,1);
	menuCursor.addComponent<SpriteComponent>("menuCursor");

	adminMode.addComponent<TransformComponent>(1792, 952, 128, 128, 1);
	adminMode.addComponent<SpriteComponent>("adminMode");
	adminMode.addComponent<ColliderComponent>("adminMode");
	adminModeActive = false;

}

void Menu::initNewGame()
{
	setOption = NewGame;

	playerOneEdit = false;
	playerTwoEdit = false;
	
	option1.getComponent<UILabel>().SetLabelText("Player ONE", "commodore");
	option2.getComponent<UILabel>().SetLabelText("Insert Name HERE", "commodore");
	option3.getComponent<UILabel>().SetLabelText("Player TWO", "commodore");
	option4.getComponent<UILabel>().SetLabelText("Insert Name HERE", "commodore");
	option5.getComponent<UILabel>().SetLabelText("START GAME", "commodore");
}



auto& menuComp(manager->getGroup(Game::groupMenu));
auto& menuCompButtons(manager->getGroup(Game::groupMenuButtons));

void Menu::effect()
{
	int x = rand() % 200;
	SDL_SetRenderDrawColor(Game::renderer, x, x, x, x);
	
}

void Menu::update()
{
	timerEfecto+= SDL_GetTicks() / 1000;
	
	if (timerEfecto > 5 && !activar)
	{
		activar = true;
	}
	if (timerEfecto > 6 && activar)
	{
		activar = false;
		timerEfecto = 1;
	}
	
	handleEvents();

	manager->refresh();
	manager->update();

}

void Menu::newGameOption()
{

}

void Menu::handleEvents()
{
	
	SDL_StartTextInput();
	SDL_PollEvent(&Game::event);

	SDL_GetMouseState(&Menu::mouseRect.x, &Menu::mouseRect.y);
	
	switch (Game::event.type)
	{
	case SDL_QUIT:
		Game::menuIsRunning = false;
		break;
	case SDLK_ESCAPE:
		Game::menuIsRunning = false;
		break;
	case SDL_TEXTINPUT:
		if (stamp!=Game::event.text.timestamp)
		{
			if (playerOneEdit)
			{
				playerOneName.append(Game::event.text.text);

			}

			if (playerTwoEdit)
			{
				playerTwoName.append(Game::event.text.text);
			}
			stamp = Game::event.text.timestamp;
		}
		break;
	case SDL_TEXTEDITING:
		break;
	case SDL_KEYDOWN:
		if (Game::event.key.keysym.sym == SDLK_RETURN)
		{
			
		}
		if (Game::event.key.keysym.sym == SDLK_BACKSPACE && playerOneName.length() > 0 && playerOneEdit)
		{
			playerOneName.pop_back();
		}
		if (Game::event.key.keysym.sym == SDLK_BACKSPACE && playerTwoName.length() > 0 && playerTwoEdit)
		{
			playerTwoName.pop_back();
		}
		break;
	case SDL_MOUSEMOTION:

		for (auto& m : menuCompButtons)
		{
			SDL_Rect menuCol = m->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(mouseRect, menuCol))
			{
				
				
				Vector2D mostrar = m->getComponent<TransformComponent>().position;
				mostrar.x -= 60;
				mostrar.y -= 12;
				menuCursor.getComponent<TransformComponent>().position = mostrar;
				cursorActivo = true;
				SDL_Delay(25);
			}
	
		}
		SDL_Rect adminCol = adminMode.getComponent<ColliderComponent>().collider;
		if (Collision::AABB(mouseRect, adminCol))
		{
			adminModeActive = true;
		}
		else
			adminModeActive = false;

		break;

	case SDL_MOUSEBUTTONDOWN:

		if (Game::event.button.clicks == 1 && Game::event.button.timestamp!=mouseButton)
		{
			mouseButton = Game::event.button.timestamp;
			Mix_PlayChannel(-1, Game::assets->GetEffect("menuSound"), 0);
			SDL_Delay(50);

			SDL_Rect startCol = option1.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, startCol))
			{
				if (setOption == Start)
				{
					Game::isRunning = true;
					Game::menuIsRunning = false;
					for (auto& m : menuComp)
					{
						m->destroy();
					}
					for (auto& m : menuCompButtons)
					{
						m->destroy();
					}
				}
			}

			SDL_Rect option2Col = option2.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, option2Col))
			{
				switch (setOption)
				{
				case Start:
					initNewGame();
					SDL_Delay(100);
					break;
				case NewGame:
					playerOneEdit = true;
					playerTwoEdit = false;
					break;
				default:
					break;
				}
			}

			SDL_Rect option4Col = option4.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, option4Col))
			{
				switch (setOption)
				{
				case NewGame:
					playerOneEdit = false;
					playerTwoEdit = true;
					break;
				default:
					break;
				}

			}

			SDL_Rect quitCol = quit.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, quitCol))
			{

				Game::menuIsRunning = false;

			}
		}
		if (Game::event.button.clicks==2 && adminModeActive)
		{
			

		}
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}

	if (playerOneEdit)
	{
		option2.getComponent<UILabel>().SetLabelText(playerOneName.c_str(), "commodore");
	}
	if (playerTwoEdit)
	{
		option4.getComponent<UILabel>().SetLabelText(playerTwoName.c_str(), "commodore");
	}


}

void Menu::draw()

{
	SDL_RenderClear(Game::renderer);
	if (!activar)
	{
		for (auto& m : menuComp)
		{
			m->draw();

		}
		for (auto& m : menuCompButtons)
		{
			m->draw();

		}
	}
	else
		this->effect();
	if (cursorActivo)
		menuCursor.draw();
	if (adminModeActive) {

		adminMode.draw();

	}
		
	SDL_RenderPresent(Game::renderer);

}