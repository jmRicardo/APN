#pragma once
#include "ECS/Components.h"
#include <string>



class LightComponent : public Component
{
public:


	SDL_Rect light;
	SDL_Texture* tex;
	std::string tag;
	TransformComponent* transform;		

	LightComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/light2.png");

	}

	void update() override
	{
		if (tag == "player" || tag == "player2")
		{
			light.x = static_cast<int>(transform->position.x) - 96;
			light.y = static_cast<int>(transform->position.y) - 96;
			light.w = 256;
			light.h = 256;
		}

		if (tag == "terminal")
		{
			light.x = static_cast<int>(transform->position.x) - 80;
			light.y = static_cast<int>(transform->position.y)-64;
			light.w = 192;
			light.h = 192;
		}

	}


	void draw() override
	{
		
		SDL_SetRenderTarget(Game::renderer, Game::fogTex);


		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_ADD);

		SDL_RenderCopy(Game::renderer, tex, NULL, &light);

		SDL_SetRenderTarget(Game::renderer, NULL);

		

	}

	


};