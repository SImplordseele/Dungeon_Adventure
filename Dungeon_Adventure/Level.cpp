#include "Level.h"
Level::Level(int cam_w, int cam_h, SDL_Renderer* renderer, Player* player) {
    cam.x = 0;
    cam.y = 0;
    cam.w = cam_w;
    cam.h = cam_h;
    this->renderer = renderer;
    this->player = player;
    font = TTF_OpenFont("Fonts/font.ttf", 18);
    for (int i = 0; i < 2; i++) {
        text[i].set_font(font);
        text[i].set_renderer(renderer);
    }
}
void Level::setuptext(int x) {
    int distance = text[0].get_height();
    string tmp0 = std::to_string(x);
    string tmp1 = std::to_string(3 - x);
    string text0 = "You have " + tmp0 + " keys right now";
    string text1 = "You still need to find " + tmp1 + " keys";
    text[0].LoadTextImage(text0.c_str(), text_color);
    text[1].LoadTextImage(text1.c_str(), text_color);
    text[0].render(0, 0);
    text[1].render(0,distance);
}
Level::~Level() {
    player = NULL;
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
    player->resetkey();
    player->setMapSize(LEVEL_WIDTH, LEVEL_HEIGHT);
    Key key1("Sprites/Key.png", 192, 768, 0, 0, renderer);
    Key key2("Sprites/Key.png", 576, 768, 0, 0, renderer);
    Key key3("Sprites/Key.png", 1152, 768, 0, 0, renderer);
    if (lv == 2) {
        key1.changepos(192, 672);
        key2.changepos(1536, 384);
        key3.changepos(1056, 384);
    }
    else if (lv == 3) {
        key1.changepos(1824, 576);
        key2.changepos(96, 864);
        key3.changepos(1824, 1152);
    }
    else if (lv == 4) {
        key1.changepos(288,1152);
        key2.changepos(1440,1344);
        key3.changepos(1536,384);
    }
    else if (lv == 5) {
        key1.changepos(288, 1536);
        key2.changepos(2400, 1152);
        key3.changepos(1440, 96);
    }
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
                return 8;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
                    running = false;
                    return 8;
                }
                if (e.key.keysym.sym == SDLK_h || e.key.keysym.sym == SDLK_F1) {
                    cout << Help(Help_document) << "\n";
                }
            }
            player->HandleEvent(e, key1, key2, key3);
            if (player->open_door(e) == true) {
                lv++;
                if (lv == 6) {
                    SDL_Delay(1000);
                }
                return lv;
            }
        }
        player->setCam(cam, LEVEL_WIDTH, LEVEL_HEIGHT);
        level->rendermap(cam);
        key1.render(cam);
        key2.render(cam);
        key3.render(cam);
        player->render(cam.x, cam.y);
        setuptext(player->getpickedkeynumber());
        if (player->move_Player() == falling) {
            player->spotify.death_sound();
            return falling;
        }
        SDL_RenderPresent(renderer);
    }
    return 1;
}

