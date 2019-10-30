#pragma once
#include "ECS/Components.h"
#include <string>



class LightComponent : public Component
{
public:


	SDL_Rect light;
	SDL_Rect lLantern;
	SDL_Texture* tex;
	SDL_Texture* texLantern;

	SDL_Texture* texture;

	

	SDL_Rect destiny = { 0,0,800,640 };

	SDL_Rect fog;
	
	std::string tag;

	SDL_Rect srcR, destR;

	TransformComponent* transform;

	

	LightComponent(std::string t)
	{
		tag = t;
		texture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 640);
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/light.jpg");

		srcR = { 0, 0, 192, 192 };
		destR = { light.x, light.y, light.w, light.h };

		texLantern = TextureManager::LoadTexture("assets/lantern.png");

	}

	void update() override
	{
		if (tag == "player" || tag == "player2")
		{
			light.x = static_cast<int>(transform->position.x) - 96;
			light.y = static_cast<int>(transform->position.y) - 96;
			light.w = 256;
			light.h = 256;
			destR.w = light.w;
			destR.h = light.h;

			lLantern.x = static_cast<int>(transform->position.x) - 128;
			lLantern.y = static_cast<int>(transform->position.y) - 32;
			lLantern.w = 128;
			lLantern.h = 192;

		}
	
		destR.x = light.x;
		destR.y = light.y;

	

	}


	void draw() override
	{
		
		SDL_SetRenderTarget(Game::renderer, texture);

		SDL_RenderCopy(Game::renderer, tex, NULL, &light);

		SDL_SetRenderTarget(Game::renderer, NULL);


		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);

		SDL_RenderCopy(Game::renderer, texture, NULL, NULL);

	}

	


};