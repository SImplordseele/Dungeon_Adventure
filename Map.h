#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "Tile.h"
#include <fstream>
using std::ifstream;
const int TILE_EMPTY = 0;
const int TILE_FLOOR = 1;
const int TILE_RIGHT_WALL = 2;
const int TILE_LEFT_WALL = 3;
const int TILE_DOOR = 4;
const int TILE_HOLE = 5;
const int TOTAL_TILE_SPRITES = 6;
class Map {
public:
	int TOTAL_TILES;
	Tile** tiles;
	Map(int tile_number, string map_tile_src, string img, SDL_Renderer* renderer);
	~Map();
	void setMapSize(int tile_x, int tile_y);
	void setMapsrc(string path);
	void LoadTile();
	bool check_collision(SDL_Rect a, SDL_Rect b);
	void rendermap(SDL_Rect& cam);
private:
	string mapsrc;
	Texture tileTexture;
	SDL_Rect* tileClips;
	int map_width;
	int map_height;
};