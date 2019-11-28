#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
private:

public:

	bool up,down,left,right;
	int upK,downK,leftK,rightK,actionK;
	bool clickState;	

	TransformComponent *transform;
	SpriteComponent *sprite;

	// manera provisoria de recibir las teclas para poder mover el personaje
	// lo ideal seria conseguir un keyCode pero por ahora lo manejo con char
	// puede traer muchos errores si la tecla no esta dentro del codigo ASCII

	KeyboardController(char up,char down,char left,char right, char action)
	{
		upK = int(up);
		downK = int(down);
		leftK = int(left);
		rightK = int(right);
		actionK = int(action);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			
			int key = Game::event.key.keysym.sym;
			if (key == upK)
			{
				transform->velocity.y = -1;
				sprite->Play("up");
				up = true;
			}
			if (key == leftK)
			{
				transform->velocity.x = -1;
				sprite->Play("left");
				left = true;
			}
			if (key == rightK)
			{
				transform->velocity.x = 1;
				sprite->Play("right");
				right = true;
			}
			if (key == downK)
			{
				transform->velocity.y = 1;
				sprite->Play("down");
				down = true;
			}
			if (key == actionK)
			{
				clickState = true;
			}
			/*switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("up");
				up = true;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("left");
				left = true;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("right");
				right = true;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("down");
				down = true;
				break;
			case SDLK_e:
				break;
			default:
				break;
			}*/
			if (left && down)
			{
				transform->velocity.x = -0.795;
				transform->velocity.y = 0.795;
				sprite->Play("left");
			}
			if (down && right)
			{
				transform->velocity.x = 0.795;
				transform->velocity.y = 0.795;
				sprite->Play("right");
			}
			if (right && up)
			{
				transform->velocity.x = 0.795;
				transform->velocity.y = -0.795;
				sprite->Play("right");
			}
			if (up && left)
			{
				transform->velocity.x = -0.795;
				transform->velocity.y = -0.795;
				sprite->Play("left");
			}
		}
	
		if (Game::event.type == SDL_KEYUP)
		{
			down = up = left = right = false;
			transform->velocity.Zero();
			sprite->Play("Idle");
			clickState = false;
		}	
	}

	bool getClickState()
	{
		return clickState;
	}
};