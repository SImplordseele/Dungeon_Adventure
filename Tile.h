#pragma once
#include <SDL.h>
const int TILE_WIDTH = 96;
const int TILE_HEIGHT = 96;
class Tile {
public:
	SDL_Rect rect;
	Tile(int x, int y, int type);
	Tile() {};
	~Tile();
	int getType();
	SDL_Rect getRect();
	void setType(int type);
private:
	int tile_type;
};