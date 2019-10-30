
#include "ECS/TimerComponent.h"

extern Manager manager;


auto& lights(manager.getGroup(Game::groupLights));

void LightComponent::preDraw()
{
	SDL_SetRenderTarget(Game::renderer, texture);

	SDL_RenderCopy(Game::renderer, tex, NULL, &light);

	SDL_SetRenderTarget(Game::renderer, NULL);
	/*SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_MOD);
	TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);*/
}