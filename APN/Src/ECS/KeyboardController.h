#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:

	bool up,down,left,right;

	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("up");
				up = true;
				break;
			case SDLK_LEFT:
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("left");
				//sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				left = true;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("right");
				right = true;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Idle");
				down = true;
				break;
			case SDLK_e:
				Game::i = 0;
				break;
			default:
				break;
			}
			if (left && down)
			{
				transform->velocity.x = -0.795;
				transform->velocity.y = 0.795;
			}
			if (down && right)
			{
				transform->velocity.x = 0.795;
				transform->velocity.y = 0.795;
			}
			if (right && up)
			{
				transform->velocity.x = 0.795;
				transform->velocity.y = -0.795;
			}
			if (up && left)
			{
				transform->velocity.x = -0.795;
				transform->velocity.y = -0.795;
			}
		}
	
		if (Game::event.type == SDL_KEYUP)
		{
			down = up = left = right = false;
			transform->velocity.y = 0;
			transform->velocity.x = 0;
			/*switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
				
				sprite->Play("Idle");
				break;
			case SDLK_LEFT:
			case SDLK_a:
				
				sprite->Play("Idle");
	
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;		
			case SDLK_ESCAPE:
				Game::isRunning = false;
			case SDLK_e:
				Game::i = 1;
				break;
			default:
				break;
			}*/
		}		
	}
};