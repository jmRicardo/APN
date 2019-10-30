#include "Menu.h"
#include "ECS\Components.h"
#include "Collision.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "Players.h"

Manager* manager;

SDL_Rect Menu::mouseRect;


std::string Menu::pOneName;
std::string Menu::pTwoName;



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
auto& adminModeScreen(manager->addEntity());

SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 155, 0, 0, 50 };
SDL_Color grey = { 110, 110,110, 255 };
SDL_Color red = { 255,0,0,255 };


void Menu::init()
{
	setOption = Start;


	menuBack.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	menuBack.addComponent<SpriteComponent>("menuBackgroundHD");
	menuBack.addGroup(Game::groupMenu);


	logoS.addComponent<UILabel>(152, 107, "A programmer's", "pixel", black);
	logoS.addGroup(Game::groupMenu);
	logo2S.addComponent<UILabel>(152, 147, "NIGHTMARE!", "pixelBig", black);
	logo2S.addGroup(Game::groupMenu);

	logo.addComponent<UILabel>(150, 105, "A programmer's", "pixel", white);
	logo.addGroup(Game::groupMenu);
	logo2.addComponent<UILabel>(150, 145, "NIGHTMARE!", "pixelBig", white);
	logo2.addGroup(Game::groupMenu);
	
	option1.addComponent<UILabel>(450, 350, "CONTINUE", "commodore", white);
	option1.addComponent<TransformComponent>(450, 350, 60, 350, 1);
	option1.addComponent<ColliderComponent>("menuCursor");
	option1.addGroup(Game::groupMenuButtons);

	option2.addComponent<UILabel>(450, 415, "NEW GAME", "commodore", white);
	option2.addComponent<TransformComponent>(450, 415, 60, 350, 1);
	option2.addComponent<ColliderComponent>("menuCursor");
	option2.addGroup(Game::groupMenuButtons);

	option3.addComponent<UILabel>(450, 480, "OPTIONS", "commodore", white);
	option3.addComponent<TransformComponent>(450, 480, 60, 350, 1);
	option3.addComponent<ColliderComponent>("menuCursor");
	option3.addGroup(Game::groupMenuButtons);

	option4.addComponent<UILabel>(450, 545, "CREDITS", "commodore", white);
	option4.addComponent<TransformComponent>(450, 545, 60, 350, 1);
	option4.addComponent<ColliderComponent>("menuCursor");
	option4.addGroup(Game::groupMenuButtons);

	option5.addComponent<UILabel>(450, 610, "HIGH SCORE", "commodore", white);
	option5.addComponent<TransformComponent>(450, 610, 60, 350, 1);
	option5.addComponent<ColliderComponent>("menuCursor");
	option5.addGroup(Game::groupMenuButtons);

	quit.addComponent<UILabel>(450, 675, "QUIT", "commodore", white);
	quit.addComponent<TransformComponent>(450, 675, 60, 350, 1);
	quit.addComponent<ColliderComponent>("menuCursor");
	quit.addGroup(Game::groupMenuButtons);

	menuCursor.addComponent<TransformComponent>(0,0,70,450,1);
	menuCursor.addComponent<SpriteComponent>("menuCursor");

	adminMode.addComponent<TransformComponent>(1238, 640, 128, 128, 1);
	adminMode.addComponent<SpriteComponent>("adminMode");
	adminMode.addComponent<ColliderComponent>("adminMode");
	adminModeActive = false;

	adminModeScreen.addComponent<TransformComponent>(0, 0, 768, 1366, 1);
	adminModeScreen.addComponent<SpriteComponent>("adminModeScreen");



}

void Menu::initNewGame()
{
	setOption = NewGame;

	playerOneEdit = false;
	playerTwoEdit = false;
	
	option1.getComponent<UILabel>().SetLabelText("Player ONE", "commodore");
	//option2.getComponent<UILabel>().SetLabelText("Insert Name HERE", "commodore");
	option2.getComponent<UILabel>().~UILabel();
	option2.addComponent<UILabel>(450, 415, "Insert Name HERE", "commodore", red);

	option3.getComponent<UILabel>().SetLabelText("Player TWO", "commodore");
	//option4.getComponent<UILabel>().SetLabelText("Insert Name HERE", "commodore");
	option4.getComponent<UILabel>().~UILabel();
	option4.addComponent<UILabel>(450, 545, "Insert Name HERE", "commodore", red);


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
	bool pOneIs = false;
	bool pTwoIs = false;

	if (setOption==NewGame)
		SDL_StartTextInput();

	SDL_PollEvent(&Game::event);

	SDL_GetMouseState(&mouseRect.x, &mouseRect.y);
	
	switch (Game::event.type)
	{

	case SDL_QUIT:

		Game::menuIsRunning = false;
		break;

	case SDLK_ESCAPE:

		Game::menuIsRunning = false;
		break;

	case SDL_TEXTINPUT:

		if (stamp != Game::event.text.timestamp)
		{
			if (playerOneEdit && pOneName.length() < 10)
			{
				pOneName.append(Game::event.text.text);

			}

			if (playerTwoEdit && pTwoName.length() < 10)
			{
				pTwoName.append(Game::event.text.text);
			}
			stamp = Game::event.text.timestamp;
		}
		break;

	case SDL_KEYDOWN:

		switch (Game::event.key.keysym.sym)
		{
		case SDLK_RETURN:
			break;
		case SDLK_TAB:
			break;
		case SDLK_BACKSPACE:
			if (pOneName.length() > 0 && playerOneEdit)
				pOneName.pop_back();
			if (pTwoName.length() > 0 && playerTwoEdit)
				pTwoName.pop_back();
			SDL_Delay(50);
			break;
		default:
			break;
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

		if (Game::event.button.clicks == 1 && Game::event.button.timestamp != mouseButton)
		{
			mouseButton = Game::event.button.timestamp;
			Mix_PlayChannel(-1, Game::assets->GetEffect("menuSound"), 0);
			SDL_Delay(50);

			SDL_Rect startCol = option1.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, startCol))
			{
				if (setOption == Start)
				{

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

			SDL_Rect option5Col = option5.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, option5Col))
			{
				switch (setOption)
				{
				case NewGame:
					char pOneCHar[20];
					char pTwoCHar[20];
					strcpy(pOneCHar, pOneName.c_str());
					strcpy(pTwoCHar, pTwoName.c_str());

					pOneIs = checkPlayer(pOneCHar);
					pTwoIs = checkPlayer(pTwoCHar);


					if (!pOneIs && !pTwoIs)
					{
						Game::isRunning = true;
						Game::menuIsRunning = false;
					}

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
		if (Game::event.button.clicks == 2 && adminModeActive && Game::event.button.timestamp != mouseButton)
		{
			mouseButton = Game::event.button.timestamp;
			createAdminProcess();

		}
		break;
	}

	if (playerOneEdit)
	{
		option2.getComponent<UILabel>().SetLabelText(pOneName.c_str(), "commodore");
	}
	if (playerTwoEdit)
	{
		option4.getComponent<UILabel>().SetLabelText(pTwoName.c_str(), "commodore");
	}


}




void Menu::createAdminProcess()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	si.lpTitle = "A programmer's Nightmare";

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA(NULL,"APNAdmin.exe",NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
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
		adminModeScreen.draw();
		adminMode.draw();

	}
		
	SDL_RenderPresent(Game::renderer);

}