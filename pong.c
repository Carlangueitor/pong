#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "game.h"

Game *Pong;

void draw_board() {
	const unsigned int segment_width = 5;
	const unsigned int segment_height = 10;
	const unsigned int segment_spacing = 15;

	SDL_SetRenderDrawColor(Pong->renderer, 0xFF, 0xFF, 0xFF,
			SDL_ALPHA_OPAQUE);

	for(int i=0; i<=Pong->screen.height; i=i+segment_height+segment_spacing) {
		SDL_Rect division_segment_rect = {
			(Pong->screen.width / 2) - (segment_width / 2),
			i,
			segment_width,
			segment_height,
		};
		SDL_RenderFillRect(Pong->renderer, &division_segment_rect);
	}
}

void draw_players() {
	SDL_SetRenderDrawColor(Pong->renderer, 0xFF, 0xFF, 0xFF,
			SDL_ALPHA_OPAQUE);
	for(int i = 0; i<2; i++) {
		SDL_Rect playerRect = {
			Pong->players[i].pos_x,
			Pong->players[i].pos_y,
			Pong->players[i].width,
			Pong->players[i].height,
		};
		SDL_RenderFillRect(Pong->renderer, &playerRect);
	}

}

void draw_ball() {
	SDL_SetRenderDrawColor(Pong->renderer, 0xFF, 0xFF, 0xFF,
			SDL_ALPHA_OPAQUE);
	SDL_Rect ball_rect = {
		Pong->ball.pos_x,
		Pong->ball.pos_y,
		Pong->ball.width,
		Pong->ball.width,
	};
	SDL_RenderFillRect(Pong->renderer, &ball_rect);
}

void game_init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		exit(1);
	}

	Pong->window = SDL_CreateWindow("Test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			Pong->screen.width,
			Pong->screen.height,
			SDL_WINDOW_OPENGL);
	if(Pong->window == NULL) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		exit(1);
	}

	Pong->renderer = SDL_CreateRenderer(Pong->window,
			-1,
			SDL_RENDERER_ACCELERATED);
	if (Pong->renderer == NULL) {
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		exit(1);
	}
	SDL_SetRenderDrawColor(Pong->renderer,
		0x00,
		0x00,
		0x00,
		SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Pong->renderer);
	SDL_RenderPresent(Pong->renderer);
}

void game_quit() {
	SDL_DestroyRenderer(Pong->renderer);
	SDL_DestroyWindow(Pong->window);
	SDL_Quit();
}

void handle_key_event(SDL_Keycode keycode) {
	SDL_Event quit_event;
	switch(keycode) {
		case SDLK_q:
			quit_event.type = SDL_QUIT;
			SDL_PushEvent(&quit_event);
			break;
		case SDLK_UP:
			Pong->players[0].pos_y -= 5;
			break;
		case SDLK_DOWN:
			Pong->players[0].pos_y += 5;
			break;
	}
}

int main(int argc, char* argv[]) {
	SDL_Event event;
	Pong = malloc(sizeof(Game));
	Pong = CreateGame();

	game_init();
	
	while(Pong->running) {
		SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				Pong->running = SDL_FALSE;
				break;
			case SDL_KEYDOWN:
				handle_key_event(event.key.keysym.sym);
				break;
		}
		SDL_SetRenderDrawColor(Pong->renderer, 0x00, 0x00, 0x00,
				SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Pong->renderer);
		draw_board();
		draw_players();
		draw_ball();
		SDL_RenderPresent(Pong->renderer);
		SDL_Delay(20);
	}

	game_quit();
	return 0;
}
