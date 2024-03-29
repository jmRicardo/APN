#include "AssetManager.h"
#include "ECS\Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::DelTexture(std::string id)
{
	textures.erase(id);
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}

void AssetManager::AddEffect(std::string id, const char* path)
{
	effects.emplace(id, Mix_LoadWAV(path));
}

Mix_Chunk* AssetManager::GetEffect(std::string id)
{
	return effects[id];
}

void AssetManager::AddMusic(std::string id, const char* path)
{
	music.emplace(id, Mix_LoadMUS(path));
}

Mix_Music* AssetManager::GetMusic(std::string id)
{
	return music[id];
}

