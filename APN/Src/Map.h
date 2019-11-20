#pragma once
#include <string>
#include "Vector2D.h"



class Map 
{
public:
	 
	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	Vector2D getPos(int buscado);

private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
	int matriz[20][25];

};
