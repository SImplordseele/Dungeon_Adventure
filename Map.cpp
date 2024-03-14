#include "Map.h"
Map::Map(int tile_number, string map_tile_src, string img_src, SDL_Renderer* renderer) {
	mapsrc = map_tile_src;
	tileTexture.set_renderer(renderer);
	tileTexture.LoadFileImage(img_src);
	TOTAL_TILES = tile_number;
	tiles = new Tile*[TOTAL_TILES];
	tileClips = new SDL_Rect[TOTAL_TILE_SPRITES];
}
Map::~Map() {
	delete[]tileClips;
	delete[]tiles;
} 
void Map::setMapsrc(string src) {
	mapsrc = src;
}
void Map::LoadTile() {
	int x = 0; 
	int y = 0;
	ifstream in;
	in.open(mapsrc);
	if (in.fail()) {
		cout << "Can not open file\n";
		return;
	}
	else {
		for (int i = 0; i < TOTAL_TILES; i++) {
			int type = -1;
			in >> type;
			if (in.fail()) {
				cout << "Can not read file\n";
				return;
			}
			if (type >= 0 && type < TOTAL_TILE_SPRITES) {
				tiles[i] = new Tile(x, y, type);
			}
			else {
				cout << "Tile is not suitable\n";
				return;
			}
			x += TILE_WIDTH;
			if (x >= map_width) {
				x = 0;
				y += TILE_HEIGHT;
			}
		}
		for (int i = 0; i < TOTAL_TILE_SPRITES; i++) {
			tileClips[i].x = i * TILE_WIDTH;
			tileClips[i].y = 0;
			tileClips[i].w = TILE_WIDTH;
			tileClips[i].h = TILE_HEIGHT;
		}
	}
	in.close();
}
void Map::setMapSize(int tile_x, int tile_y) {
	map_width = tile_x * TILE_WIDTH;
	map_height = tile_y * TILE_HEIGHT;
	TOTAL_TILES = tile_x * tile_y;
}
bool Map::check_collision(SDL_Rect a, SDL_Rect b) {
	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;
	left_a = a.x; right_a = a.x + a.w;
	left_b = b.x; right_b = b.x + b.w;
	top_a = a.y; bottom_a = a.y + a.h;
	top_b = b.y; bottom_b = b.y + b.h;
	if (left_a >= right_b || left_b >= right_a || top_a >= bottom_b || top_b >= bottom_a) return false;
	return true;
}
void Map::rendermap(SDL_Rect& cam) {
	for (int i = 0; i < TOTAL_TILES; i++) {
		if (check_collision(cam, tiles[i]->getRect())) {
			int x_pos = tiles[i]->rect.x - cam.x;
			int y_pos = tiles[i]->rect.y - cam.y;
			tileTexture.render(x_pos, y_pos, &tileClips[tiles[i]->getType()]);
		}
	}
}