#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
using std::cout;
using std::string;
class Texture {
public:
	Texture();
	~Texture();
	int get_width();
	int get_height();
	void set_renderer(SDL_Renderer* renderer);
	void set_font(TTF_Font* font);
	bool LoadFileImage(string path);
	void LoadTextImage(string text, SDL_Color color);
	void render(int x, int y, SDL_Rect* clip = NULL);
	SDL_Texture* getTexture();
	void free();
private:
	int width;
	int height;
	SDL_Texture* texture = NULL;
	TTF_Font* font = NULL;
	SDL_Renderer* renderer = NULL;
};