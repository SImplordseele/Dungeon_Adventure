#include "Level.h"
Level::Level(int cam_w, int cam_h, SDL_Window* window, SDL_Renderer* renderer, Player* player) {
    cam.x = 0;
    cam.y = 0;
    cam.w = cam_w;
    cam.h = cam_h;
    this->window = window;
    this->renderer = renderer;
    this->player = player;
}
Level::~Level() {
    player = NULL;
    window = NULL;
    renderer = NULL;
    level = NULL;
}
void Level::SetLevel(int x, int y) {
    LEVEL_WIDTH = x * TILE_WIDTH;
    LEVEL_HEIGHT = y * TILE_HEIGHT;
}
SDL_Texture* Level::LoadTexture(string path) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        cout << "Can not load image\n";
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        surface = NULL;
    }
    return texture;
}

void Level::LoadLevel(Map* level) {
    this->level = level;
    this->level->LoadTile();
    player->SetlevelMap(level);
}
int Level::PlayLevel() {
    player->setMapSize(LEVEL_WIDTH, LEVEL_HEIGHT);
    Key key1("Sprites/Key.png", 192, 768, 0, 0, renderer);
    Key key2("Sprites/Key.png", 576, 768, 0, 0, renderer);
    Key key3("Sprites/Key.png", 1152, 768, 0, 0, renderer);
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
                return 3;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
                    running = false;
                    return 3;
                }
                if (e.key.keysym.sym == SDLK_h || e.key.keysym.sym == SDLK_F1) {
                    cout << Help(Help_document) << "\n";
                }
            }
            player->HandleEvent(e, key1, key2, key3);
            if (player->open_door(e) == true) {
                return 4;
            }
        }
        SDL_RenderClear(renderer);
        if (player->move_Player() == falling) {
            return falling;
        }
        player->setCam(cam, LEVEL_WIDTH, LEVEL_HEIGHT);
        level->rendermap(cam);
        key1.render(cam);
        key2.render(cam);
        key3.render(cam);
        player->render(cam.x, cam.y);
        SDL_RenderPresent(renderer);
    }
    return 1;
}

