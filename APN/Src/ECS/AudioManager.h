#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class AudioManager : public Component
{
public:

	AudioManager()
	{
		
	}
	
	void update() override
	{
		if (Game::event.type == SDL_JOYBUTTONDOWN)
		{
			

		}

	}
private:

};