#include "Tile.h"
Tile::Tile(int x, int y, int type) {
	rect.x = x;
	rect.y = y;
	rect.w = TILE_WIDTH;
	rect.h = TILE_HEIGHT;
	tile_type = type;
}
Tile::~Tile() {};
int Tile::getType() {
	return this->tile_type;
}
SDL_Rect Tile::getRect() {
	return this->rect;
}
void Tile::setType(int type) {
	this->tile_type = type;
}
