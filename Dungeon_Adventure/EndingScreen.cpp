#include "EndingScreen.h"
EndingScreen::EndingScreen(SDL_Renderer* renderer,Player* player,TTF_Font* font) {
	this->renderer = renderer;
	this->player = player;
	this->font = font;
	ending = new Text[2];
}
EndingScreen::~EndingScreen() {
	delete[]ending;
	ending = NULL;
	renderer = NULL;
	player->objectTexture.free();
	player = NULL;
	font = NULL;
}
SDL_Texture* EndingScreen::setTexture(TTF_Font* font, string text, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void EndingScreen::setup() {
	ending[0].text = "THANKS";
	ending[0].position.w = 300;
	ending[0].position.h = 100;
	ending[0].position.x = (SCREEN_WIDTH - 300)/2;
	ending[0].position.y = 50;
	ending[0].texture = setTexture(font, ending[0].text, color);
	ending[1].text = "FOR PLAYING";
	ending[1].position.x = (SCREEN_WIDTH-500)/2;
	ending[1].position.y = 300;
	ending[1].position.w = 500;
	ending[1].position.h = 100;
	ending[1].texture = setTexture(font, ending[1].text, color);
}
void EndingScreen::player_render(int x, int y, SDL_Rect* clip) {
	SDL_Rect rect = { x, y, clip->w, clip->h };
	SDL_RenderCopy(renderer, player->objectTexture.getTexture(), clip, &rect);
}
int EndingScreen::play() {
	Uint32 starttime;
	int sprite = 0;
	SDL_Event e;
	while (true) {
		starttime = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if ((e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)) || e.type == SDL_QUIT) {
				return 8;
			}
		}
		SDL_RenderClear(renderer);
		SDL_Rect tmp = player->getclipright(sprite);
		player_render(SCREEN_WIDTH/2 - Player_sprite_width/2, SCREEN_HEIGHT/2 - Player_sprite_height/2, &tmp);
		for (int i = 0; i < 2; i++) {
			SDL_RenderCopy(renderer, ending[i].texture, NULL, &ending[i].position);
		}
		SDL_RenderPresent(renderer);
		Uint32 remain_time = SDL_GetTicks() - starttime;
		if (remain_time < 100) {
			SDL_Delay(100 - remain_time);
		}
		sprite++;
		if (sprite >= 8) sprite = 0;
	}
}