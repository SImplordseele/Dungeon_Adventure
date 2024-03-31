#include "Texture.h"
Texture::Texture() {
    width = 0;
    height = 0;
}
Texture::~Texture() {
    free();
}
int Texture::get_height() {
    return height;
}
int Texture::get_width() {
    return width;
}
void Texture::set_renderer(SDL_Renderer* renderer) {
   this->renderer = renderer;
}
void Texture::set_font(TTF_Font* gFont) {
    this->font = gFont;
}
bool Texture::LoadFileImage(string path) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* Surface = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(renderer, Surface);
    width = Surface->w;
    height = Surface->h;
    texture = newTexture;
    SDL_FreeSurface(Surface);
    newTexture = NULL;
    return (texture != NULL);
}
void Texture::LoadTextImage(string text, SDL_Color textColor) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, 600);
    if (textSurface == NULL) {
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == NULL) {
        return;
    }
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);
}
void Texture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect rect = { x, y, width, height };
    if (clip != NULL) {
        rect.w = clip->w;
        rect.h = clip->h;
    }
    SDL_RenderCopy(renderer, texture, clip, &rect);
}
void Texture::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}
SDL_Texture* Texture::getTexture() {
    return this->texture;
}
