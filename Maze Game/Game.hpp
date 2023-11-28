#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <string.h>
using namespace std;

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 850;

const int LEVEL_WIDTH = 2000;
const int LEVEL_HEIGHT = 954;

// const int MAZE_ROW = 138;
// const int MAZE_COLUMN = 383;

const int SIZE = 10;

const int DestX = 950;
const int DestY = 350;

const int PlayerInitialX = 330; // 330
const int PlayerInitialY = 460; // 460

const int EnemyInitialX = 1550;
const int EnemyInitialY = 350;



class Game
{
private:
	SDL_Texture *playerTexture = NULL;
	SDL_Texture *enemyTexture = NULL;
	SDL_Texture *finishTexture = NULL;

	SDL_Texture *healthTexture= NULL;
	int t = 0;

	// SDL_Surface *bgSurface = NULL;
	// SDL_Texture *bgTexture = NULL;

	// SDL_Color rgb;

	// SDL_Rect rect;



	// int SIZE = 20;

	// int DestX = 8;
	// int DestY = 11;

public:
	Game();
	~Game();

	SDL_Window *window;
	SDL_Renderer *renderer;

	bool isRunning;

	Mix_Music *gMusic = NULL;

	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	void timeshow(TTF_Font *font);

	void EnemyHandleUpdateRender();

	bool running() { return isRunning; }

	void health();
	void restaurant();

	void boost();

	bool isWON = false;
	bool isLOSS = false;

	int slow = 0;
	int playerSlow = 0;

	int isTIMELEFT = true;

	int startTime = 0;
	int t1 = 0;
    int t2 = 1;

	string time = "Time Left  01:00";

	SDL_Surface *timeSurface = NULL;

	int playerSpeed = 1;
	int enemySpeed = 2;

	int healthStatus = 6;

	bool istext = false;

	// int idx = 0;
	// string enemyList[] = level1;
};

#endif