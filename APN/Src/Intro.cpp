#include "Intro.h"
#include "TextureManager.h"



Intro::Intro()
{
}

void Intro::init()
{
	x = y = z = o =  0;
	skipIntro = false;
	background = TextureManager::LoadTexture("assets/spaceHD.png");
}

void Intro::play()
{
	init();
	while (!skipIntro)
	{

		frameStart = SDL_GetTicks();
		
		update();
		draw();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
}

void Intro::update()
{


	number.clear();
	number.append(std::to_string(o)+ std::to_string(z)+ std::to_string(y)+ std::to_string(x));
	path = "assets/starWars/introJPG/intro_0" + number + ".jpg";
	letters = TextureManager::LoadTexture(path.c_str());
	x++;
	std::cout << number << std::endl;
	if (x == 10)
	{
		x = 0;
		y++;
	}
	if (y == 10) {
		y = 0;
		z++;
	}
	if (z == 10) {
		z = 0;
		o++;
	}
	SDL_PollEvent(&Game::event);

	if (Game::event.type == ( SDL_KEYDOWN ) || atoi(number.c_str())>1625 || Game::event.type == (SDL_MOUSEBUTTONDOWN))
	{
		skipIntro = true;
	}
	

}

void Intro::draw()
{
	SDL_RenderClear(Game::renderer);
	SDL_SetTextureAlphaMod(background, 200);
	SDL_RenderCopy(Game::renderer, background, NULL, NULL);	
	TextureManager::DrawWithBlendMode(letters, SDL_BLENDMODE_ADD);	
	SDL_RenderPresent(Game::renderer);
	SDL_DestroyTexture(letters);
	
}
