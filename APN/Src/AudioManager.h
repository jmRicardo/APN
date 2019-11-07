#pragma once

#include "AssetManager.h"


class AudioManager
{
public:

	static void PlayMusic(const char* play)
	{
		Mix_FadeOutMusic(350);
		//Mix_PlayMusic(Game::assets->GetMusic(play), -1);
		Mix_FadeInMusic(Game::assets->GetMusic(play), -1,500);
	}
	
	static void PauseMusic()
	{
		//Mix_Pause(-1);
		Mix_PauseMusic();
	}
	static void ResumeMusic()
	{
		Mix_ResumeMusic();
	}
	static void SetVolume(int x)
	{
		Mix_VolumeMusic(x);
	}

};