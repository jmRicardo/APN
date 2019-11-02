#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;
		
		Animation up = Animation(0, 9, 100);
		Animation left = Animation(1, 9, 100);
		Animation down = Animation(2, 9, 100);
		Animation right = Animation(3, 9, 100);
		Animation Idle = Animation(2, 1, 100);
		
		animations.emplace("up", up);
		animations.emplace("left", left);
		animations.emplace("down", down);		
		animations.emplace("right", right);
		animations.emplace("Idle", Idle);
	

		Play("Idle");

		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated, bool gameOver)
	{
		if (gameOver)
		{
			animated = isAnimated;

			Animation end = Animation(0, 20, 100);

			animations.emplace("end", end);

			Play("end");

			setTex(id);


		}
	}

	SpriteComponent(std::string id, bool isAnimated, bool gameOver,bool enemy)
	{
		if (enemy)
		{
			animated = isAnimated;

			Animation right = Animation(0, 9, 100);
			Animation left = Animation(1, 9, 100);

			animations.emplace("right", right);
			animations.emplace("left", left);

			Play("right");

			setTex(id);


		}
	}
	~SpriteComponent()
	{
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

	SDL_Texture* gameOverTex()
	{
		return texture;
	}

	SDL_Rect gameOverSRect()
	{
		return srcRect;
	}
	

};