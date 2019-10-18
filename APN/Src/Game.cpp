#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>
#include "Menu.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Joystick* gGameController = nullptr;
SDL_Cursor* nCursor = nullptr;

SDL_Rect Game::camera = { 0,0,1920,1080};

AssetManager* Game::assets = new AssetManager(&manager);

Menu* Game::menu = new Menu(&manager);

bool Game::isRunning = false;
bool Game::menuIsRunning = false;
int Game::i = 0;

auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& player2(manager.addEntity());
auto& key(manager.addEntity());
auto& rain(manager.addEntity());



Game::Game()
{}

Game::~Game()
{}
void Game::inicCursor()
{
	SDL_Surface* surface = nullptr;
	surface = IMG_Load("assets/hc.png");
	nCursor = SDL_CreateColorCursor(surface, 0, 0);
	SDL_SetCursor(nCursor);
}
void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Error : MIX_OPENAUDIO" << Mix_GetError() << std::endl;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("player2", "assets/korby.png");
	assets->AddTexture("projectile", "assets/proj.png");
	assets->AddTexture("key", "assets/keyT.png");
	assets->AddTexture("rain", "assets/rain.png");
	assets->AddTexture("fog", "assets/fogT.png");
	assets->AddTexture("fogP", "assets/fogP.png");
	assets->AddTexture("menuBackground", "assets/space800.jpg");
	assets->AddTexture("menuBackgroundHD", "assets/spaceHD.png");
	assets->AddTexture("menuCursor", "assets/menuCursor.png");
	assets->AddTexture("me", "assets/yo.png");


	assets->AddFont("arial", "assets/arial.ttf", 32);
	assets->AddFont("pixel", "assets/dp.ttf", 22);
	assets->AddFont("pixelBig", "assets/dp.ttf", 50);
	assets->AddFont("commodore", "assets/commodore.ttf", 32);

	assets->AddEffect("bomb", "assets/nice-work.wav");
	assets->AddEffect("org", "assets/org.wav");
	assets->AddEffect("hadu", "assets/hadouryu.wav");

	assets->AddMusic("intro", "assets/castelvania.mp3");
	

	SDL_Color white = { 255, 255, 255, 255 };
	
	label.addComponent<UILabel>(250, 600, "Test String", "arial", white);

	menu->init();

	//Mix_PlayMusic(assets->GetMusic("intro"), -1);

	inicCursor();

	menuIsRunning = true;
}

void Game::menuInit()
{
	menu->update();
	menu->draw();	
	
}

void Game::loadGame()
{
	SDL_ShowCursor(SDL_DISABLE);
	
	map = new Map("terrain", 1, 32);
	//ecs implementation

	map->LoadMap("assets/map.map", 25, 20);



	key.addComponent<TransformComponent>(250, 250, 32, 32, 1);
	key.addComponent<SpriteComponent>("key");
	key.addComponent<ColliderComponent>("key");

	player.addComponent<TransformComponent>(400, 320, 64, 64, 2);
	player.addComponent<SpriteComponent>("me", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addComponent<JoystickController>(0);
	player.addGroup(groupPlayers);

	/*player2.addComponent<TransformComponent>(600.f, 600.f, 32, 32, 1);
	player2.addComponent<SpriteComponent>("player2", true);
	player2.addComponent<KeyboardController>();
	player2.addComponent<ColliderComponent>("player2");
	//player2.addComponent<JoystickController>(1);
	player2.addGroup(groupPlayers);*/

	

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& tilesFog = tiles;

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	case SDLK_ESCAPE:
		isRunning = false;
		break;
	default:
		break;
	}
}



void Game::update()
{	

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	//SDL_Rect playerCol2 = player2.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	//Vector2D playerPos2 = player2.getComponent<TransformComponent>().position;
	SDL_Rect keyCol = key.getComponent<ColliderComponent>().collider;
	Vector2D keyPos = key.getComponent<TransformComponent>().position;

	/*std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "pixel");*/

	manager.refresh();
	manager.update();


	
	
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
		/*if (Collision::AABB(cCol, playerCol2))
		{
			player2.getComponent<TransformComponent>().position = playerPos2;
		}*/
	}

	for (auto& p : players)
	{
		if (Collision::AABB(keyCol,playerCol))
		{
			std::cout << "agarraste la llave hijo de puta" << std::endl;
		}

	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}
	/*TileComponent* cambiar;
	for (auto& t : tiles)
	{
		
		cambiar = &t->getComponent<TileComponent>();
		std::cout << cambiar->position.x <<" "<< cambiar->position.x << std::endl;
		
		cambiar->texture = Game::assets->GetTexture("fogT");
		//SDL_Delay(1000);
	}
	*/

	/*camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;*/
}

void Game::render()
{
	SDL_RenderClear(renderer);
	TileComponent* cambiar;
	
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	//int x = playerPos.x / player


	for (auto& t : tiles)
	{
		t->draw();
	}
	
	if (Game::i == 1) {

		for (auto& t : tilesFog)
		{
			cambiar = &t->getComponent<TileComponent>();
			//cambiar->texture = Game::assets->GetTexture("fog");
			TextureManager::Draw(Game::assets->GetTexture("fog"), cambiar->srcRect, cambiar->destRect, SDL_FLIP_NONE);

		}

	}
	/*for (auto& c : colliders)
	{
		c->draw();
	}*/
	
	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	key.draw();
	label.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}