#include "Map.h"
Map::Map(int tile_number, string map_tile_src, string img_src, SDL_Renderer* renderer) {
    mapsrc = map_tile_src;
    tileTexture.set_renderer(renderer);
    tileTexture.LoadFileImage(img_src);
    TOTAL_TILES = tile_number;
    tiles = new Tile * [TOTAL_TILES];
    tileClips = new SDL_Rect[TOTAL_TILE_SPRITES];
}
Map::~Map() {
    delete[]tiles;
    delete[]tileClips;
}
void Map::setMapSize(int tile_x, int tile_y) {
    map_width = tile_x * TILE_WIDTH;
    map_height = tile_y * TILE_HEIGHT;
    TOTAL_TILES = tile_x * tile_y;
}
void Map::setMapsrc(string src) {
    mapsrc = src;
}
void Map::LoadTile() {
    int x = 0;
    int y = 0;
    ifstream source;
    source.open(mapsrc);
    if (source.fail()) {
        cout << "No file\n";
        return;
    }
    else {
        for (int i = 0; i < TOTAL_TILES; ++i) {
            int type = -1;
            source >> type;
            if (source.fail()) {
                return;
            }
            if (type >= 0 && type < TOTAL_TILE_SPRITES) {
                tiles[i] = new Tile(x, y, type);
            }
            else {
                return;
            }
            x += TILE_WIDTH;
            if (x >= map_width){
                x = 0;
                y += TILE_HEIGHT;
            }
        }
        for (int i = 0; i < TOTAL_TILE_SPRITES; ++i) {
            tileClips[i].x = i * TILE_WIDTH;
            tileClips[i].y = 0;
            tileClips[i].w = TILE_WIDTH;
            tileClips[i].h = TILE_HEIGHT;
        }
    }
    source.close();
}
bool Map::check_collision(SDL_Rect a, SDL_Rect b) {
    int left_a, right_a, top_a, bottom_a;
    int left_b, right_b, top_b, bottom_b;
    left_a = a.x; right_a = a.x + a.w;
    top_a = a.y; bottom_a = a.y + a.h;
    left_b = b.x; right_b = b.x + b.w;
    top_b = b.y; bottom_b = b.y + b.h;
    if (top_a >= bottom_b || top_b >= bottom_a || left_a >= right_b || left_b >= right_a) return false;
    return true;
}
void Map::rendermap(SDL_Rect& cam) {
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (check_collision(cam, tiles[i]->getRect())) {
            tileTexture.render(tiles[i]->rect.x - cam.x, tiles[i]->rect.y - cam.y, &tileClips[tiles[i]->getType()]);
        }
    }
}

