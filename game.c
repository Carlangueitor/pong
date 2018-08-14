#include <stdlib.h>
#include <string.h>
#include "game.h"

const unsigned int DEFAULT_SCREEN_WIDTH = 1024;
const unsigned int DEFAULT_SCREEN_HEIGHT = 768;
const unsigned int PLAYER_WIDTH = 15;
const unsigned int PLAYER_HEIGHT = 45;
const unsigned int BALL_WIDTH = 15;

Game *CreateGame() {
	Game *game = malloc(sizeof(Game));
	game->running = SDL_TRUE;
	game->screen = (struct Screen){
		DEFAULT_SCREEN_WIDTH,
		DEFAULT_SCREEN_HEIGHT
	};

	game->ball = (Ball){
		DEFAULT_SCREEN_WIDTH / 2,
		DEFAULT_SCREEN_HEIGHT / 2,
		BALL_WIDTH
	};

	Player players[2] = {
		{0, DEFAULT_SCREEN_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT},
		{DEFAULT_SCREEN_WIDTH - PLAYER_WIDTH, DEFAULT_SCREEN_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT}
	};
	memcpy(game->players, players, sizeof(players));

	return game;
}
