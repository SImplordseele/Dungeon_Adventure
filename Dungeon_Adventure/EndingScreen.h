#pragma once
#include "Player.h"
struct Text {
	string text;
	SDL_Texture* texture;
	SDL_Rect position;
};
class EndingScreen {
public:
	EndingScreen(SDL_Renderer* renderer,Player* player,TTF_Font* font);
	~EndingScreen();
	int play();
	void setup();
	void player_render(int x, int y, SDL_Rect* clip);
	SDL_Texture* setTexture(TTF_Font* font, string text, SDL_Color color);
private:
	Text* ending ;
	SDL_Color color = { 255,255,255 };
	TTF_Font* font = NULL;
	Player* player = NULL;
	SDL_Renderer* renderer = NULL;
};