#ifndef GAME
#define GAME

#include <SDL2/SDL.h>

struct Screen {
	unsigned int width;
	unsigned int height;
};

typedef struct Player {
	unsigned int pos_x;
	unsigned int pos_y;
	unsigned int width;
	unsigned int height;
} Player;

typedef struct Ball {
	unsigned int pos_x;
	unsigned int pos_y;
	unsigned int width;
} Ball;

typedef struct Game {
	Ball ball;
	Player players[2];
	SDL_bool running;
	struct Screen screen;
	SDL_Renderer *renderer;
	SDL_Window *window;
} Game;

Game *CreateGame();

#endif
