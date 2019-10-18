#include "Menu.h"
#include "ECS\Components.h"
#include "Collision.h"

Manager* manager;

SDL_Rect Menu::mouseRect;


Menu::Menu(Manager* man) 
{
	manager = man;
}

Menu::~Menu()
{}

auto& menuBack(manager->addEntity());
auto& logo(manager->addEntity());
auto& logoS(manager->addEntity());
auto& logo2(manager->addEntity());
auto& logo2S(manager->addEntity());
auto& start(manager->addEntity());
auto& newGame(manager->addEntity());
auto& options(manager->addEntity());
auto& credits(manager->addEntity());
auto& score(manager->addEntity());
auto& quit(manager->addEntity());
auto& menuCursor(manager->addEntity());

SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 155, 0, 0, 50 };
SDL_Color grey = { 110, 110,110, 255 };


void Menu::init()
{
	
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
	
	start.addComponent<UILabel>(650, 400, "CONTINUE", "commodore", white);
	start.addComponent<TransformComponent>(650, 400, 60, 350, 1);
	start.addComponent<ColliderComponent>("menuCursor");
	start.addGroup(Game::groupMenuButtons);

	newGame.addComponent<UILabel>(650, 465, "NEW GAME", "commodore", white);
	newGame.addComponent<TransformComponent>(650, 465, 60, 350, 1);
	newGame.addComponent<ColliderComponent>("menuCursor");
	newGame.addGroup(Game::groupMenuButtons);

	options.addComponent<UILabel>(650, 530, "OPTIONS", "commodore", white);
	options.addComponent<TransformComponent>(650, 530, 60, 350, 1);
	options.addComponent<ColliderComponent>("menuCursor");
	options.addGroup(Game::groupMenuButtons);

	credits.addComponent<UILabel>(650, 595, "CREDITS", "commodore", white);
	credits.addComponent<TransformComponent>(650, 595, 60, 350, 1);
	credits.addComponent<ColliderComponent>("menuCursor");
	credits.addGroup(Game::groupMenuButtons);

	score.addComponent<UILabel>(650, 660, "HIGH SCORE", "commodore", white);
	score.addComponent<TransformComponent>(650, 660, 60, 350, 1);
	score.addComponent<ColliderComponent>("menuCursor");
	score.addGroup(Game::groupMenuButtons);

	quit.addComponent<UILabel>(650, 725, "QUIT", "commodore", white);
	quit.addComponent<TransformComponent>(650, 725, 60, 350, 1);
	quit.addComponent<ColliderComponent>("menuCursor");
	quit.addGroup(Game::groupMenuButtons);

	menuCursor.addComponent<TransformComponent>(0,0,70,450,1);
	menuCursor.addComponent<SpriteComponent>("menuCursor");
}

void Menu::initNewGame()
{
	
}

auto& menuComp(manager->getGroup(Game::groupMenu));
auto& menuCompButtons(manager->getGroup(Game::groupMenuButtons));



std::string piloto = "";
std::string composicion;
Sint32 cursor;
Sint32 slen;
Uint32 timerEfecto;
Vector2D Cord;
Uint32 boton;
bool activar;
bool Menu::cursorActivo = false;


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
	

	//SDL_Delay(50);
	SDL_StartTextInput();
	SDL_PollEvent(&Game::event);
	
	switch (Game::event.type)
	{
	case SDL_QUIT:
		Game::isRunning = false;
		break;

	case SDL_TEXTINPUT:	
		
		piloto.append(Game::event.text.text);
		
		std::cout << "muestra = " << piloto << std::endl;

		std::cout << "compo = " << composicion << std::endl;
		std::cout << "cursor = " << cursor << std::endl;
		std::cout << "slen = " << slen << std::endl;
		break;
	case SDL_TEXTEDITING:

		composicion = Game::event.edit.text;
		cursor = Game::event.edit.start;
		slen = Game::event.edit.length;
		break;
	case SDL_KEYDOWN:
		if (Game::event.key.keysym.sym == SDLK_RETURN)
		{
			this->initNewGame();
			for (auto& m : menuCompButtons)
			{
				m->destroy();
			}
		}		
		if (Game::event.key.keysym.sym == SDLK_BACKSPACE && piloto.length() > 0)
			piloto.pop_back();
		break;
	case SDL_MOUSEMOTION:
		boton = SDL_GetMouseState(&Menu::mouseRect.x, &Menu::mouseRect.y);
		for (auto& m : menuCompButtons)
		{
			SDL_Rect menuCol = m->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, menuCol))
			{
				Vector2D mostrar = m->getComponent<TransformComponent>().position;
				mostrar.x -= 60;
				mostrar.y -= 12;
				menuCursor.getComponent<TransformComponent>().position = mostrar;
				Menu::cursorActivo = true;
			}


			SDL_Rect startCol = start.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, startCol))
			{
				if (boton)
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
			SDL_Rect quitCol = quit.getComponent<ColliderComponent>().collider;
			if (Collision::AABB(Menu::mouseRect, quitCol))
			{
				if (boton)
					Game::menuIsRunning = false;
			
			}
		

		}
		break;
	default:
		break;
	}
	//logo.getComponent<UILabel>().SetLabelText(piloto, "pixel");

	manager->refresh();
	manager->update();

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
	if (Menu::cursorActivo)
		menuCursor.draw();
	SDL_RenderPresent(Game::renderer);

}