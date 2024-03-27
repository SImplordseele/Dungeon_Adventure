#include "Player.h"
Player::Player(string path, int x_pos, int y_pos, int x_velocity, int y_velocity, SDL_Renderer* renderer, Map* level) :
    Object(path, x_pos, y_pos, x_velocity, y_velocity, renderer) {
    LoadPlayer();
    curr_frame = 0;
    curr_sprite = clip_right[0];
    this->level = level;
    picked_key_number = 0;
    startX = x_pos;
    startY = y_pos;
}
Player::~Player() {
    objectTexture.free();
    level = NULL;
}
void Player::LoadPlayer() {
    for (int i = 0; i < TOTAL_PLAYER_SPRITE; ++i) {
        clip_left[i].x = i * Player_sprite_width;
        clip_left[i].y = 0;
        clip_left[i].w = Player_sprite_width;
        clip_left[i].h = Player_sprite_height;
    }
    for (int i = 0; i < TOTAL_PLAYER_SPRITE; ++i) {
        clip_right[i].x = i * Player_sprite_width;
        clip_right[i].y = Player_sprite_height;
        clip_right[i].w = Player_sprite_width;
        clip_right[i].h = Player_sprite_height;
    }
    for (int i = 0; i < TOTAL_PLAYER_SPRITE; ++i) {
        clip_up[i].x = i * Player_sprite_width;
        clip_up[i].y = 2 * Player_sprite_height;
        clip_up[i].w = Player_sprite_width;
        clip_up[i].h = Player_sprite_height;
    }
    for (int i = 0; i < TOTAL_PLAYER_SPRITE; ++i) {
        clip_down[i].x = i * Player_sprite_width;
        clip_down[i].y = 3 * Player_sprite_height;
        clip_down[i].w = Player_sprite_width;
        clip_down[i].h = Player_sprite_height;
    }
}
void Player::SetlevelMap(Map* level) {
    this->level = level;
}
void Player::SetPlayerPos(int x_pos, int y_pos) {
    sprite_rect.x = x_pos;
    sprite_rect.y = y_pos;
    startX = x_pos;
    startY = y_pos;
}
void Player::HandleEvent(SDL_Event& e, Key& key1, Key& key2, Key& key3) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            y_vel -= y_velocity;
            curr_sprite = clip_up[0];
            break;
        case SDLK_DOWN:
            y_vel += y_velocity;
            curr_sprite = clip_down[0];
            break;
        case SDLK_RIGHT:
            x_vel += x_velocity;
            curr_sprite = clip_right[0];
            break;
        case SDLK_LEFT:
            x_vel -= x_velocity;
            curr_sprite = clip_left[0];
            break;
        case SDLK_SPACE:
            pickupKey(key1);
            pickupKey(key2);
            pickupKey(key3);
            break;
        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            y_vel += y_velocity;
            curr_sprite = clip_up[0];
            break;
        case SDLK_DOWN:
            y_vel -= y_velocity;
            curr_sprite = clip_down[0];
            break;
        case SDLK_RIGHT:
            x_vel -= x_velocity;
            curr_sprite = clip_right[0];
            break;
        case SDLK_LEFT:
            x_vel += x_velocity;
            curr_sprite = clip_left[0];
            break;
        case SDLK_SPACE:
            pickupKey(key1);
            pickupKey(key2);
            pickupKey(key3);
            break;
        default:
            break;
        }
    }
}
bool Player::check_collision(SDL_Rect a, SDL_Rect b) {
    int left_a, right_a, top_a, bottom_a;
    int left_b, right_b, top_b, bottom_b;
    left_a = a.x; right_a = a.x + a.w;
    top_a = a.y; bottom_a = a.y + a.h;
    left_b = b.x; right_b = b.x + b.w;
    top_b = b.y; bottom_b = b.y + b.h;
    if (top_a >= bottom_b || top_b >= bottom_a || left_a >= right_b || left_b >= right_a) return false;
    return true;
}
int Player::collide_with_wall(Tile* tiles[], int tiles_number, int TILE_FLOOR, int TILE_HOLE) {
    for (int i = 0; i < tiles_number; ++i) {
        int tileType = tiles[i]->getType();
        if (tileType != TILE_FLOOR && tileType != TILE_HOLE) {
            if (check_collision(sprite_rect, tiles[i]->getRect())) {
                return touch_wall;
            }
        }
        if (tileType == TILE_HOLE) {
            SDL_Rect tile = tiles[i]->getRect();
            if (sprite_rect.x >= tile.x && sprite_rect.x + sprite_rect.w <= tile.x + tile.w) {
                if (sprite_rect.y + sprite_rect.h <= tile.y + tile.h && sprite_rect.y + sprite_rect.h / 2 >= tile.y) {
                    return fall_hole;
                }
            }
        }
    }
    return walk_freely;
}
int Player::move_Player() {
    int pixelsPerFrameChange = 1;
    int frameCount = 0;
    int initX = sprite_rect.x;
    int initY = sprite_rect.y;
    int positionOnTile;
    if (x_vel > 0) {
        while (sprite_rect.x <= initX + x_vel) {
            sprite_rect.x += pixelsPerFrameChange;
            positionOnTile = collide_with_wall(level->tiles, level->TOTAL_TILES, TILE_FLOOR, TILE_HOLE);
            if (sprite_rect.x + Player_sprite_width > map_width || positionOnTile == touch_wall) {
                sprite_rect.x -= pixelsPerFrameChange;
                break;
            }
            if (positionOnTile == fall_hole) {
                return falling;
            }
            frameCount++;
            if (frameCount >= TOTAL_PLAYER_SPRITE) {
                frameCount = 0;
            }
            curr_sprite = clip_right[frameCount];
            spotify.walk_sound();
        }
    }
    if (x_vel < 0) {
        while (sprite_rect.x >= initX + x_vel) {
            sprite_rect.x -= pixelsPerFrameChange;
            positionOnTile = collide_with_wall(level->tiles, level->TOTAL_TILES, TILE_FLOOR, TILE_HOLE);
            if (sprite_rect.x < 0 || positionOnTile == touch_wall) {
                sprite_rect.x += pixelsPerFrameChange;
                break;
            }
            if (positionOnTile == fall_hole) {
                return falling;
            }
            frameCount++;
            if (frameCount >= TOTAL_PLAYER_SPRITE) {
                frameCount = 0;
            }
            curr_sprite = clip_left[frameCount];
            spotify.walk_sound();
        }
    }
    if (y_vel > 0) {
        while (sprite_rect.y <= initY + y_vel) {
            sprite_rect.y += pixelsPerFrameChange;
            positionOnTile = collide_with_wall(level->tiles, level->TOTAL_TILES, TILE_FLOOR, TILE_HOLE);
            if (sprite_rect.y + Player_sprite_height > map_height || positionOnTile == touch_wall) {
                sprite_rect.y -= pixelsPerFrameChange;
                break;
            }
            if (positionOnTile == fall_hole) {
                return falling;
            }
            frameCount++;
            if (frameCount >= TOTAL_PLAYER_SPRITE) {
                frameCount = 0;
            }
            curr_sprite = clip_down[frameCount];
            spotify.walk_sound();
        }
    }
    if (y_vel < 0) {
        while (sprite_rect.y >= initY + y_vel) {
            sprite_rect.y -= pixelsPerFrameChange;
            positionOnTile = collide_with_wall(level->tiles, level->TOTAL_TILES, TILE_FLOOR, TILE_HOLE);
            if (sprite_rect.y < 0 || positionOnTile == touch_wall) {
                sprite_rect.y += pixelsPerFrameChange;
                break;
            }
            if (positionOnTile == fall_hole) {
                return falling;
            }
            frameCount++;
            if (frameCount >= TOTAL_PLAYER_SPRITE) {
                frameCount = 0;
            }
            curr_sprite = clip_up[frameCount];
            spotify.walk_sound();
        }
    }
    return 1;
}
void Player::setCam(SDL_Rect& cam, int w, int h) {
    cam.x = (sprite_rect.x + Player_sprite_width / 2) - SCREEN_WIDTH / 2;
    cam.y = (sprite_rect.y + Player_sprite_height / 2) - SCREEN_HEIGHT / 2;
    if (cam.x < 0) {
        cam.x = 0;
    }
    if (cam.y < 0) {
        cam.y = 0;
    }
    if (cam.x > w - cam.w) {
        cam.x = w - cam.w;
    }
    if (cam.y > h - cam.h) {
        cam.y = h - cam.h;
    }
}
void Player::pickupKey(Key& key) {
    if (key.Ispicked() == false) {
        if (check_collision(Player::sprite_rect, key.get_rect())) {
            key.pick();
            spotify.pick_sound();
            SDL_Delay(400);
            picked_key_number++;
        }
    }
}
bool Player::open_door(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
        for (int i = 0; i < level->TOTAL_TILES; i++) {
            int tileType = level->tiles[i]->getType();
            if (tileType == TILE_DOOR) {
                SDL_Rect rect = level->tiles[i]->getRect();
                for (int j = 0; j < 4; j++) {
                    if (sprite_rect.x >= rect.x + dx1[j]  && sprite_rect.x <= rect.x + dx2[j]
                        && sprite_rect.y >= rect.y + dy1[j] && sprite_rect.y <= rect.y + dy2[j]) {
                        if (picked_key_number == TOTAL_KEY) {
                            spotify.open_sound();
                            return true;
                        }
                        else {
                            spotify.knock_sound();
                            SDL_Delay(1000);
                        }
                    }
                }
            }
        }
    }
    return false;
}
void Player::render(int camX, int camY) {
    objectTexture.render(sprite_rect.x - camX, sprite_rect.y - camY, &curr_sprite);
}
void Player::resetkey() {
    picked_key_number = 0;
}
SDL_Rect Player::getclipright(int i) {
    return clip_right[i];
}
int Player::getpickedkeynumber() {
    return picked_key_number;
}
