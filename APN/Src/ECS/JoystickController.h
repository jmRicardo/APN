#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"


class JoystickController : public Component
{
public:
	TransformComponent* transform = nullptr;
	SpriteComponent* sprite = nullptr;
	SDL_Joystick* gGameController = nullptr;
	Sint16 x_move = 0, y_move = 0;
	int buttons = 0;

	JoystickController(int joy) {
		
		gGameController = SDL_JoystickOpen(joy);
		buttons = SDL_JoystickNumButtons(gGameController);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		
		if (SDL_JoystickGetButton(gGameController, 0))
			Mix_PlayChannel(-1, Game::assets->GetEffect("bomb"), 0);


		if (SDL_JoystickGetButton(gGameController, 1))
			Mix_PlayChannel(-1, Game::assets->GetEffect("org"), 0);
		
		if (SDL_JoystickGetButton(gGameController, 2))
		{
			Mix_PlayChannel(-1, Game::assets->GetEffect("hadu"), 0);
			Game::assets->CreateProjectile(Vector2D(400,285), Vector2D(2, 0), 200, 2, "projectile");
		}
		

		if (Game::event.type == SDL_JOYAXISMOTION)
		{ 
			x_move = SDL_JoystickGetAxis(gGameController, 0);
			y_move = SDL_JoystickGetAxis(gGameController, 1);	
			std::cout << "X: " << x_move << " Y: " << y_move << std::endl;
			/*if (x_move < DZ && )
				x_move = 0;
			if (y_move)*/
			if (x_move > 0)
				if (x_move - DZ > 0)
				transform->velocity.x = 1;
			if (x_move < 0)
				if (x_move + DZ < 0)
					transform->velocity.x = -1;
			if (y_move > 0)
				if (y_move - DZ > 0)
				transform->velocity.y = 1;
			if (y_move < 0)
				if (y_move + DZ < 0)
					transform->velocity.y = -1;
			if (x_move == 0)
				transform->velocity.x = 0;
			if (y_move == 0)
				transform->velocity.y = 0;
		}
	}

private:

	const int DZ = 8000;
};