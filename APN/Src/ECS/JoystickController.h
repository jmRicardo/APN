#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"


class JoystickController : public Component
{
private:

	TransformComponent* transform = nullptr;
	SpriteComponent* sprite = nullptr;
	SDL_Joystick* gGameController = nullptr;
	Sint16 x_move = 0, y_move = 0;
	int buttons = 0;
	Uint8 dpad;
	bool clickState;
	const int DZ = 8000;

public:
	JoystickController(int joy) {
		
		gGameController = SDL_JoystickOpen(joy);
		buttons = SDL_JoystickNumButtons(gGameController);
		clickState = false;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	bool getClickState()
	{
		return clickState;
	}

	void update() override
	{
		clickState = SDL_JoystickGetButton(gGameController, 0) ? true : false;

		SDL_PollEvent(&Game::event);
		dpad = SDL_JoystickGetHat(gGameController, 0);

	if (Game::event.type)
	{
			
			switch (dpad)
			{
			case SDL_HAT_UP:
				sprite->Play("up");
				transform->velocity.y = -1;
				break;
			case SDL_HAT_DOWN:
				sprite->Play("down");
				transform->velocity.y = 1;
				break;
			case SDL_HAT_LEFT:
				sprite->Play("left");
				transform->velocity.x = -1;
				break;
			case SDL_HAT_RIGHT:
				sprite->Play("right");
				transform->velocity.x = 1;
				break;
			case SDL_HAT_CENTERED:
				sprite->Play("Idle");
				transform->velocity.Zero();
				break;
			case SDL_HAT_LEFTDOWN:
				transform->velocity.x = -0.795;
				transform->velocity.y = 0.795;
				sprite->Play("left");				
				break;
			case SDL_HAT_LEFTUP:
				transform->velocity.x = -0.795;
				transform->velocity.y = -0.795;
				sprite->Play("left");
				break;
			case SDL_HAT_RIGHTDOWN:
				transform->velocity.x = 0.795;
				transform->velocity.y = 0.795;
				sprite->Play("right");
				break;
			case SDL_HAT_RIGHTUP:
				transform->velocity.x = 0.795;
				transform->velocity.y = -0.795;
				sprite->Play("right");
				break;
			default:
				break;
			}
	
	} 
		
		


		

		/*if (Game::event.type == SDL_JOYAXISMOTION)
		{ 
			x_move = SDL_JoystickGetAxis(gGameController, 0);
			y_move = SDL_JoystickGetAxis(gGameController, 1);	
			std::cout << "X: " << x_move << " Y: " << y_move << std::endl;
			if (x_move < DZ && )
				x_move = 0;
			if (y_move)
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
		if (Game::event.type == SDL_JOYHATMOTION)
		{

		}*/
	}


};