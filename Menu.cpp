#include "Menu.h"
Menu::Menu(int w, int h, SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
	menu_width = w;
	menu_height = h;
	menu_window = window;
	menu_renderer = renderer;
	menu_font = font;
	menu_Button = new Button[BUTTON_TOTAL];
}
Menu::~Menu() {
	delete[]menu_Button;
	menu_font = NULL;
	menu_window = NULL;
	menu_renderer = NULL;
	menu_font = NULL;
/*
	if (menu_font != NULL) {
		TTF_CloseFont(menu_font);
		menu_font = NULL;
	}
	if (menu_window != NULL) {
		SDL_DestroyWindow(menu_window);
		menu_window = NULL;
	}
	if (menu_renderer != NULL) {
		SDL_DestroyRenderer(menu_renderer);
		menu_renderer = NULL;
	}
	if (title != NULL) {
		title = NULL;
	}
*/
}
SDL_Texture* Menu::setTexture(TTF_Font* font, string text, SDL_Color color) {
	SDL_Surface* tmp = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(menu_renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

void Menu::setupMenu() {
	menu_Button[0].Text = "Start";
	menu_Button[0].hover = false;
	menu_Button[0].position.x = 110;
	menu_Button[0].position.y = 200;
	menu_Button[0].position.w = BUTTON_WIDTH;
	menu_Button[0].position.h = BUTTON_HEIGHT;
	menu_Button[0].texture = setTexture(menu_font, menu_Button[0].Text, color[0]);

	menu_Button[1].Text = "Help";
	menu_Button[1].hover = false;
	menu_Button[1].position.x = 242;
	menu_Button[1].position.y = 300;
	menu_Button[1].position.w = BUTTON_WIDTH;
	menu_Button[1].position.h = BUTTON_HEIGHT;
	menu_Button[1].texture = setTexture(menu_font, menu_Button[1].Text, color[0]);

	menu_Button[2].Text = "Exit";
	menu_Button[2].hover = false;
	menu_Button[2].position.x = 370;
	menu_Button[2].position.y = 200;
	menu_Button[2].position.w = BUTTON_WIDTH;
	menu_Button[2].position.h = BUTTON_HEIGHT;
	menu_Button[2].texture = setTexture(menu_font, menu_Button[2].Text, color[0]);

	title = setTexture(menu_font, "DUNGEON ADVENTURE", color[0]);
	title_pos.x = 100;
	title_pos.y = 50;
	title_pos.w = 440;
	title_pos.h = 150;
}
int Menu::showMenu() {
	SDL_Event e;
	int mouse_x , mouse_y;
	while (true) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_MOUSEMOTION:
					mouse_x = e.motion.x;
					mouse_y = e.motion.y;
					for (int i = 0; i < BUTTON_TOTAL; i++) {
						if (mouse_x >= menu_Button[i].position.x
							&& mouse_x <= menu_Button[i].position.x + BUTTON_WIDTH
							&& mouse_y >= menu_Button[i].position.y
							&& mouse_y <= menu_Button[i].position.y + BUTTON_HEIGHT) {
							if (menu_Button[i].hover == false) {
								menu_Button[i].hover = true;
								menu_Button[i].texture = setTexture(menu_font, menu_Button[i].Text, color[1]);
							}
						}
						else {
							if (menu_Button[i].hover == true) {
								menu_Button[i].hover = false;
								menu_Button[i].texture = setTexture(menu_font, menu_Button[i].Text, color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouse_x = e.motion.x;
					mouse_y = e.motion.y;
					for (int i = 0; i < BUTTON_TOTAL; i++) {
						if (mouse_x >= menu_Button[i].position.x
							&& mouse_x <= menu_Button[i].position.x + BUTTON_WIDTH
							&& mouse_y >= menu_Button[i].position.y
							&& mouse_y <= menu_Button[i].position.y + BUTTON_HEIGHT) {
							return i + 1;
						}
					}
					break;
				default:
					break;

			}
			SDL_RenderCopy(menu_renderer, title, NULL, &title_pos);
			for (int i = 0; i < BUTTON_TOTAL; i++) {
				SDL_RenderCopy(menu_renderer, menu_Button[i].texture, NULL, &menu_Button[i].position);
			}
			SDL_RenderPresent(menu_renderer);
		}
		return 0;
	}
}