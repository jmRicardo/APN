#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>
#include "Menu.h"
#include "EnemiesManager.h"
#include "ECS/LightComponent.h"
#include "AudioManager.h"
#include "Intro.h"
#include "MatchList.h"

Map* map;

Manager manager;


EnemiesManager* Game::eManager = nullptr;
SDL_Renderer* Game::renderer = nullptr;

bool Game::load = false;

SDL_Event Game::event;

SDL_Cursor* nCursor = nullptr;

SDL_Texture* Game::fogTex;

SDL_Rect Game::camera = { 0,0,1366,768};
SDL_Rect Game::viewPort = { 282,100,800,640};

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Texture* gameOverTex;

bool Game::isRunning = false;
bool Game::menuIsRunning = false;




auto& player(manager.addEntity());
auto& player2(manager.addEntity());
auto& labelPOne(manager.addEntity());
auto& labelPTwo(manager.addEntity());
auto& pOneMini(manager.addEntity());
auto& pTwoMini(manager.addEntity());

auto& keyPone(manager.addEntity());
auto& keyPtwo(manager.addEntity());

auto& timer(manager.addEntity());
auto& gameOver(manager.addEntity());

auto& terminal(manager.addEntity());
auto& terminal2(manager.addEntity());

auto& menuButton(manager.addEntity());
auto& quitButton(manager.addEntity());

auto& stageLevel(manager.addEntity());

auto& win(manager.addEntity());
auto& winLabel(manager.addEntity());

Game::Game()
{
}
Game::~Game()
{}

void Game::inicCursor()
{
	SDL_Surface* surface = nullptr;
	surface = IMG_Load("assets/Images/hc.png");
	nCursor = SDL_CreateColorCursor(surface, 0, 0);
	SDL_SetCursor(nCursor);
}

void Game::finalScore()
{
	AudioManager::PlayMusic("imperial");
	bool skipEnd = false;
	std::string whoWin = "¡";
	int idWho = whoWonTheMatch();
	whoWin.append((idWho == one.idPlayer ? one.nick : two.nick));	
	whoWin.append(" WIN!");
	winLabel.getComponent<UILabel>().SetLabelText(whoWin, "cLevel");
	
	win.draw();
	winLabel.draw();
	SDL_RenderPresent(renderer);

	while (!skipEnd)
	{
		SDL_PollEvent(&event);
		if (event.type == (SDL_KEYDOWN) || event.type == (SDL_MOUSEBUTTONDOWN))
		{
			skipEnd = true;
		}
	}
	menuLoad();
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
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 8192) < 0)
	{
		std::cout << "Error : MIX_OPENAUDIO" << Mix_GetError() << std::endl;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}


	///pre cargo la mayoria de los assets al inicio porque no es juego que consuma muchos recursos y puedo darme ese lujo
	assets->AddTexture("terrain", "assets/Images/level5.png");
	assets->AddTexture("player", "assets/Images/yoS.png");
	assets->AddTexture("player2", "assets/Images/yo2S.png");
	assets->AddTexture("keyDisk", "assets/Images/fdisk32.png");
	assets->AddTexture("keyDiskP2", "assets/Images/fdisk32p2.png");
	assets->AddTexture("terminal", "assets/Images/terminal1.png");
	assets->AddTexture("terminal2", "assets/Images/terminal2.png");

	assets->AddTexture("menuButton", "assets/Images/menuBoton.png");
	assets->AddTexture("quitButton", "assets/Images/quitBoton.png");
	
	assets->AddTexture("menuBackground", "assets/Images/space800.jpg");
	assets->AddTexture("menuBackgroundHD", "assets/Images/spaceHD.png");

	assets->AddTexture("menuCursor", "assets/Images/menuCursor.png");
	assets->AddTexture("adminMode", "assets/Images/adminMode.png");
	assets->AddTexture("adminModeScreen", "assets/Images/adminModeScreen.png");
	
	assets->AddTexture("pOneMini", "assets/Images/pOneMini.png");
	assets->AddTexture("pTwoMini", "assets/Images/pTwoMini.png");

	assets->AddTexture("gameOver", "assets/Images/gameOver.png");
	assets->AddTexture("DGhost", "assets/Images/DGhost.png");

	assets->AddTexture("utMinas", "assets/Images/grillaMine.png");

	assets->AddTexture("finalBack", "assets/Images/fback.png");
	

	assets->AddFont("pixel", "assets/Fonts/dp.ttf", 24);
	assets->AddFont("pixelBig", "assets/Fonts/dp.ttf", 88);
	assets->AddFont("commodore", "assets/Fonts/commodore.ttf", 40);
	assets->AddFont("cLevel", "assets/Fonts/commodore.ttf", 60);
	assets->AddFont("cCredits", "assets/Fonts/commodore.ttf", 20);

	assets->AddEffect("menuSound", "assets/Sounds/menu.mp3");
	assets->AddEffect("end", "assets/Sounds/destroyed.mp3");

	assets->AddMusic("intro", "assets/Sounds/introSong.mp3");
	assets->AddMusic("level", "assets/Sounds/levelMusic.mp3");
	assets->AddMusic("gameOver", "assets/Sounds/gameOver2.mp3");
	assets->AddMusic("starWars", "assets/Sounds/starWars.mp3");
	assets->AddMusic("imperial", "assets/Sounds/imperial.mp3");

	AudioManager::SetVolume(64);

	Intro elcho;
	AudioManager::PlayMusic("starWars");
	elcho.play();
	
	eManager = new EnemiesManager();
	

	player.addComponent<TransformComponent>(0, 0, 64, 64, 1);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addComponent<JoystickController>(0);
	player.addComponent<LightComponent>("player");
	player.addGroup(groupPlayers);


	player2.addComponent<TransformComponent>(0, 0, 64, 64, 1);
	player2.addComponent<SpriteComponent>("player2", true);
	//player2.addComponent<KeyboardController>();
	player2.addComponent<ColliderComponent>("player2");
	player2.addComponent<LightComponent>("player2");
	player2.addComponent<JoystickController>(1);
	player2.addGroup(groupPlayers);

	SDL_Color white = { 255, 255, 255, 255 };

	timer.addComponent<Timer>(666, 15, 5);

	gameOver.addComponent<TransformComponent>(0.f, 0.f, 400, 640, 1);
	gameOver.addComponent<SpriteComponent>("gameOver", true, true);

	labelPOne.addComponent<UILabel>(120, 15, Menu::pOneName, "commodore", white);
	labelPTwo.addComponent<UILabel>(926, 15, Menu::pTwoName, "commodore", white);

	/*labelPOne.addComponent<UILabel>(125, 15, "PLAYER1234", "commodore", white);
	labelPTwo.addComponent<UILabel>(926, 15, "PLAYER2345", "commodore", white);*/

	pOneMini.addComponent<TransformComponent>(50, 10, 32, 32, 2);
	pOneMini.addComponent<SpriteComponent>("pOneMini");


	pTwoMini.addComponent<TransformComponent>(1252, 10, 32, 32, 2);
	pTwoMini.addComponent<SpriteComponent>("pTwoMini");

	terminal.addComponent<TransformComponent>(0, 0, 32, 32, 1);
	terminal.addComponent<SpriteComponent>("terminal");
	terminal.addComponent<ColliderComponent>("terminal");
	terminal.addComponent<LightComponent>("terminal");

	terminal2.addComponent<TransformComponent>(0, 0, 32, 32, 1);
	terminal2.addComponent<SpriteComponent>("terminal2");
	terminal2.addComponent<ColliderComponent>("terminal2");
	terminal2.addComponent<LightComponent>("terminal2");


	keyPone.addComponent<TransformComponent>(0, 0, 32, 32, 1);
	keyPone.addComponent<SpriteComponent>("keyDisk");
	keyPone.addComponent<ColliderComponent>("key");

	keyPtwo.addComponent<TransformComponent>(0, 0, 32, 32, 1);
	keyPtwo.addComponent<SpriteComponent>("keyDiskP2");
	keyPtwo.addComponent<ColliderComponent>("key");

	menuButton.addComponent<TransformComponent>(74, 320, 128, 128, 1);
	menuButton.addComponent<SpriteComponent>("menuButton");
	menuButton.addComponent<ColliderComponent>("menuButton");

	quitButton.addComponent<TransformComponent>(1164, 320, 128, 128, 1);
	quitButton.addComponent<SpriteComponent>("quitButton");
	quitButton.addComponent<ColliderComponent>("quitButton");


	stageLevel.addComponent<UILabel>(460,350,"LEVEL","commodore",white);

	win.addComponent<TransformComponent>(0, 0, 640, 800, 1);
	win.addComponent<SpriteComponent>("finalBack");

	winLabel.addComponent<UILabel>(150, 300, "ELCHO WINS", "cLevel", white);
	

	inicCursor();
	actualLevel = 1;
	menuIsRunning = true;
	load = false;
}


void Game::menuLoad()
{
	isRunning = false;

	SDL_RenderSetViewport(Game::renderer, NULL);
	SDL_ShowCursor(SDL_ENABLE);

	AudioManager::PlayMusic("intro");

	
	menuIsRunning = true;

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& enemies(manager.getGroup(Game::groupEnemies));


void Game::loadLevel()
{
	if (actualLevel == 1)
	{
		one = gPlayerName(Menu::pOneCHar);
		two = gPlayerName(Menu::pTwoCHar);		
		initMatch(one,two);
	}
		
	
	delete map;
	SDL_RenderSetViewport(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	
	///variables del juego
	keyOne = keyTwo = false;
	pOneActive = pTwoActive = true;
	isGameOver = false;
	
	/// recarga textura del terreno y crea la instancia del mismo
	assets->DelTexture("terrain");
	std::string pathTex = "assets/Images/level"+ std::to_string(actualLevel) +".png";
	assets->AddTexture("terrain", pathTex.c_str());
	std::string path = "assets/Maps/mapLevel" + std::to_string(actualLevel) + ".map";
	map = new Map("terrain", 1, 32);
	map->LoadMap(path, 25, 20);	

	/// seteo de jugadores

	setRandomPos();
	
	/// seteo de enemigos, fog, cursor, etc

	labelPOne.getComponent<UILabel>().SetLabelText(Menu::pOneName,"commodore");
	labelPTwo.getComponent<UILabel>().SetLabelText(Menu::pTwoName,"commodore");
	
	eManager->initEnemies(5);

	fogTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 640);

	timer.getComponent<Timer>().setTimer(45);

	stage(actualLevel);

	AudioManager::PlayMusic("level");



	tiles = manager.getGroup(Game::groupMap);
	colliders = manager.getGroup(Game::groupColliders);
	SDL_ShowCursor(SDL_DISABLE);
	
	load = false;
}

void Game::scoreScreen()
{

}





void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDLK_ESCAPE:
		isRunning = false;
	
		break;
	case SDL_MOUSEBUTTONDOWN:
		mouse.x = event.button.x;
		mouse.y = event.button.y;
		mouse.w = mouse.h = 1;

		if (Collision::AABB(mouse, quitButton.getComponent<ColliderComponent>().collider))
		{
			
			menuLoad();
			actualLevel = 1;
		}
		if (Collision::AABB(mouse, menuButton.getComponent<ColliderComponent>().collider))
		{
			
			actualLevel = 1;
			loadLevel();
		}
		break;
	default:
		break;
	}	

}



void Game::update()
{	
	double send = timer.getComponent<Timer>().checkTime();
	
	
	if (send<25)
		eManager->updatePosition(send);

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	SDL_Rect playerCol2 = player2.getComponent<ColliderComponent>().collider;

	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D playerPos2 = player2.getComponent<TransformComponent>().position;

	SDL_Rect keyCol = keyPone.getComponent<ColliderComponent>().collider;
	SDL_Rect keyCol2 = keyPtwo.getComponent<ColliderComponent>().collider;

	bool clickPOne = player.getComponent<JoystickController>().getClickState();
	bool clickPTwo = player2.getComponent<JoystickController>().getClickState();

	manager.refresh();
	manager.update();	
	timer.update();
	
	
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;

		}
		if (Collision::AABB(cCol, playerCol2))
		{
			player2.getComponent<TransformComponent>().position = playerPos2;
		}
		
	}
	
	if (Collision::AABB(keyCol,playerCol))
	{
		if (clickPOne)
		{
			keyPone.getComponent<TransformComponent>().position.x = 10;
			keyPone.getComponent<TransformComponent>().position.y = 25;		
			keyOne = true;
		}
	}

	if (Collision::AABB(keyCol2, playerCol2))
	{
		if (clickPTwo)
		{
			keyPtwo.getComponent<TransformComponent>().position.x = 1324;
			keyPtwo.getComponent<TransformComponent>().position.y = 25;
			keyTwo = true;
		}
	}

	if (Collision::AABB(terminal.getComponent<ColliderComponent>().collider, playerCol))
	{
		if (keyOne && clickPOne)
		{
			actualLevel++;
			whoWonTheScreen(send, Menu::pOneCHar);
			actualLevel == 6 ? finalScore() : loadLevel();
			
		}
	}

	if (Collision::AABB(terminal2.getComponent<ColliderComponent>().collider, playerCol2))
	{
		if (keyTwo && clickPTwo)
		{
			actualLevel++;
			whoWonTheScreen(send, Menu::pTwoCHar);
			actualLevel == 6 ? finalScore() : loadLevel();
			
		}
	}

	for (auto& e : enemies)
	{
		SDL_Rect eCol = e->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCol, eCol) && pOneActive)
		{
			Mix_PlayChannel(-1, Game::assets->GetEffect("end"), 0);
			pOneActive = false;
		}

		if (Collision::AABB(playerCol2, eCol) && pTwoActive)
		{
			Mix_PlayChannel(-1, Game::assets->GetEffect("end"), 0);
			pTwoActive = false;
		}
	}



	
}




void Game::render()
{
	
	
	// LIMPIA EL FOG
	cleanFog();


	SDL_RenderClear(renderer);

	// DIBUJA LAS ENTIDADES EN EL TAMAÑO DE LA VENTANA
	SDL_RenderSetViewport(renderer, &camera);

	labelPOne.draw();
	labelPTwo.draw();

	pOneMini.draw();
	pTwoMini.draw();

	timer.draw();

	menuButton.draw();
	quitButton.draw();

	if (keyOne)	keyPone.draw();
	if (keyTwo)	keyPtwo.draw();

	// DIBUJAR DENTRO DEL VIEWPORT, OSEA DE LA VENTANA DONDE SE JUEGA
	SDL_RenderSetViewport(renderer, &viewPort);

	for (auto& t : tiles)
	{
		t->draw();
	}


/*	for (auto& c : colliders)
	{
		c->draw();
	}*/

	if (!keyOne)	keyPone.draw();
	if (!keyTwo)	keyPtwo.draw();

	terminal.draw();
	terminal2.draw();

	if (pOneActive)	player.draw();
	if (pTwoActive)	player2.draw();

	for (auto& e : enemies)
	{

		e->draw();
	}

	drawFog();

	if (timer.getComponent<Timer>().checkTime() < 1 || (!pOneActive && !pTwoActive))
	{
		if (!isGameOver)
		{
			AudioManager::PlayMusic("gameOver");
			SDL_Delay(100);
			gameOverTex = gameOver.getComponent<SpriteComponent>().gameOverTex();
			SDL_ShowCursor(SDL_ENABLE);
			isGameOver = true;

		}
	}

	if (isGameOver)	drawGameOver();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::drawFog()
{
	
	SDL_SetTextureBlendMode(fogTex, SDL_BLENDMODE_MOD);
	SDL_RenderCopy(renderer, fogTex, NULL, NULL);

}

void Game::drawGameOver()
{
	SDL_SetTextureBlendMode(gameOverTex, SDL_BLENDMODE_ADD);
	SDL_RenderCopy(renderer, gameOverTex, &gameOver.getComponent<SpriteComponent>().gameOverSRect(), NULL);
}

void Game::cleanFog()
{
	SDL_SetRenderTarget(renderer, fogTex);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
}

void intro()
{

}

void Game::stage(int x)
{
	SDL_RenderClear(renderer);
	stageLevel.getComponent<UILabel>().SetLabelText("LEVEL "+std::to_string(x),"cLevel");
	stageLevel.draw();
	SDL_RenderPresent(renderer);
	SDL_Delay(1500);
}

void Game::setRandomPos()
{
	Vector2D pOnePos = map->getPos(3);
	Vector2D pTwoPos = map->getPos(3);

	std::cout << "P1: " << pOnePos << std::endl;
	std::cout << "P2: " << pTwoPos << std::endl;
	while (pOnePos == pTwoPos)
	{
		pTwoPos = map->getPos(3);
		pOnePos = map->getPos(3);
	}
	player.getComponent<TransformComponent>().position = pOnePos;
	player2.getComponent<TransformComponent>().position = pTwoPos;

	pOnePos = map->getPos(2);
	pTwoPos = map->getPos(2);

	std::cout << "T1: " << pOnePos << std::endl;
	std::cout << "T2: " << pTwoPos << std::endl;
	while (pOnePos == pTwoPos)
	{
		pTwoPos = map->getPos(2);
		pOnePos = map->getPos(2);
	}

	terminal.getComponent<TransformComponent>().position = map->getPos(2);
	terminal2.getComponent<TransformComponent>().position = map->getPos(2);

	pOnePos = map->getPos(4);
	pTwoPos = map->getPos(4);

	std::cout << "K1: " << pOnePos << std::endl;
	std::cout << "K2: " << pTwoPos << std::endl;
	while (pOnePos == pTwoPos)
	{
		pTwoPos = map->getPos(4);
		pOnePos = map->getPos(4);
	}

	keyPone.getComponent<TransformComponent>().position = map->getPos(4);
	keyPtwo.getComponent<TransformComponent>().position = map->getPos(4);
}