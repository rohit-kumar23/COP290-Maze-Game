#include "Game.hpp"

Game *game = nullptr;

// const int SCREEN_WIDTH = 1200;
// const int SCREEN_HEIGHT = 1000;
// SDL_Renderer *renderer;

// bool loadMedia()
// {
// 	//Loading success flag
// 	bool success = true;

// 	//Load press texture
// 	if( !gDotTexture.loadFromFile( "dot.bmp" ) )
// 	{
// 		printf( "Failed to load dot texture!\n" );
// 		success = false;
// 	}

// 	return success;
// }

int showmenu(int width, int height, SDL_Renderer *renderer, TTF_Font *font)
{

    Uint32 time;
    int x, y;
    const int NUMMENU = 3;
    const char *labels[NUMMENU] = {"New Game", "Sound", "Exit"};

    SDL_Surface *menus[NUMMENU];
    bool selected[NUMMENU] = {0, 0, 0};

    SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};

    menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
    menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
    menus[2] = TTF_RenderText_Solid(font, labels[2], color[0]);

    // menus[0] = IMG_Load("resources/player1.png");
    // menus[1] = IMG_Load("resources/player1.png");

    // if( menus[0] == NULL )
    // {
    // 	printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    // }

    SDL_Rect pos[NUMMENU];

    // cout << menus[0]->h << endl;

    pos[0].x = width / 2 - menus[0]->w / 2;
    pos[0].y = height / 2 - menus[0]->h - menus[1]->h / 2;

    pos[0].w = menus[0]->w;
    pos[0].h = menus[0]->h;

    pos[1].x = width / 2 - menus[1]->w / 2;
    pos[1].y = height / 2 - menus[1]->h / 2;

    pos[1].w = menus[1]->w;
    pos[1].h = menus[1]->h;

    pos[2].x = width / 2 - menus[2]->w / 2;
    pos[2].y = height / 2 + menus[1]->h / 2;

    pos[2].w = menus[2]->w;
    pos[2].h = menus[2]->h;

    // pos[0].x = SCREEN_WIDTH / 2 - 50;
    // pos[0].y = SCREEN_HEIGHT / 2 - 50;

    // pos[1].x = SCREEN_WIDTH / 2 - 50;
    // pos[1].y = SCREEN_HEIGHT / 2 + 50;

    // SDL_FillRect(renderer, &renderer->clip_rect, SDL_MapRGB(renderer->format, 0x00, 0x00, 0x00));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Event event;

    while (1)
    {
        time = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_FreeSurface(menus[0]);
                SDL_FreeSurface(menus[1]);
                SDL_FreeSurface(menus[2]);
                return 2;

            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;

                for (int i = 0; i < NUMMENU; i++)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            SDL_FreeSurface(menus[i]);
                            menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                        }
                    }

                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            SDL_FreeSurface(menus[i]);
                            menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;

                for (int i = 0; i < NUMMENU; i++)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        for (int j = 0; j < NUMMENU; j++)
                        {
                            SDL_FreeSurface(menus[j]);
                        }
                        return i;
                    }
                }

                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    for (int i = 0; i < NUMMENU; i++)
                    {
                        SDL_FreeSurface(menus[i]);
                    }
                    // game->isRunning = false;
                    return 2;
                }
            }
        }

        for (int i = 0; i < NUMMENU; i++)
        {

            SDL_Rect destr = {200, 200, 50, 50};
            // destr.x = SCREEN_WIDTH / 2 + 100*i;
            // destr.y = SCREEN_HEIGHT / 2 + 100*i;

            // cout << "hey_" << i << endl;

            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, menus[i]);

            // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            // SDL_RenderCopy(renderer, tex, NULL, &pos[i]);
            // SDL_BlitSurface(menus[i], NULL, renderer, &pos[i]);

            SDL_RenderCopyEx(renderer, tex, NULL, &pos[i], 0.0, NULL, SDL_FLIP_NONE);

            // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            // SDL_RenderFillRect(renderer, &destr);

            // SDL_RenderPresent(renderer);
        }

        SDL_RenderPresent(renderer);

        if (1000 / 30 > SDL_GetTicks() - time)
        {
            SDL_Delay(1000 / 30 - SDL_GetTicks() + time);
        }
    }
}

int soundmenu(int width, int height, SDL_Renderer *renderer, TTF_Font *font)
{
    Uint32 time;
    int x, y;
    const int NUMMENU = 2;
    const char *labels[NUMMENU] = {"ON", "OFF"};

    SDL_Surface *menus[NUMMENU];
    bool selected[NUMMENU] = {0, 0};

    SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};

    menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
    menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);

    // menus[0] = IMG_Load("player1.png");
    // menus[1] = IMG_Load("player1.png");

    // if( menus[0] == NULL )
    // {
    // 	printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    // }

    SDL_Rect pos[NUMMENU];

    // cout << menus[0]->h << endl;

    pos[0].x = width / 2 - menus[0]->w / 2;
    pos[0].y = height / 2 - menus[0]->h;

    pos[0].w = menus[0]->w;
    pos[0].h = menus[0]->h;

    pos[1].x = width / 2 - menus[1]->w / 2;
    pos[1].y = height / 2;

    pos[1].w = menus[1]->w;
    pos[1].h = menus[1]->h;

    // pos[0].x = SCREEN_WIDTH / 2 - 50;
    // pos[0].y = SCREEN_HEIGHT / 2 - 50;

    // pos[1].x = SCREEN_WIDTH / 2 - 50;
    // pos[1].y = SCREEN_HEIGHT / 2 + 50;

    // SDL_FillRect(renderer, &renderer->clip_rect, SDL_MapRGB(renderer->format, 0x00, 0x00, 0x00));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Event event;

    while (1)
    {
        time = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_FreeSurface(menus[0]);
                SDL_FreeSurface(menus[1]);
                return 2;

            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;

                for (int i = 0; i < NUMMENU; i++)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            SDL_FreeSurface(menus[i]);
                            menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                        }
                    }

                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            SDL_FreeSurface(menus[i]);
                            menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;

                for (int i = 0; i < NUMMENU; i++)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        for (int j = 0; j < NUMMENU; j++)
                        {
                            SDL_FreeSurface(menus[j]);
                        }
                        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        // SDL_RenderClear(renderer);
                        return i;
                    }
                }

                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    for (int i = 0; i < NUMMENU; i++)
                    {
                        SDL_FreeSurface(menus[i]);
                    }
                    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    // SDL_RenderClear(renderer);
                    return 2;
                }
            }
        }

        for (int i = 0; i < NUMMENU; i++)
        {

            SDL_Rect destr = {200, 200, 50, 50};
            // destr.x = SCREEN_WIDTH / 2 + 100*i;
            // destr.y = SCREEN_HEIGHT / 2 + 100*i;

            // cout << "hey_" << i << endl;

            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, menus[i]);

            // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            // SDL_RenderCopy(renderer, tex, NULL, &pos[i]);
            // SDL_BlitSurface(menus[i], NULL, renderer, &pos[i]);

            SDL_RenderCopyEx(renderer, tex, NULL, &pos[i], 0.0, NULL, SDL_FLIP_NONE);

            // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            // SDL_RenderFillRect(renderer, &destr);

            // SDL_RenderPresent(renderer);
        }

        SDL_RenderPresent(renderer);

        if (1000 / 30 > SDL_GetTicks() - time)
        {
            SDL_Delay(1000 / 30 - SDL_GetTicks() + time);
        }
    }
}



void SOUND()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        // success = false;
    }

    game->gMusic = Mix_LoadMUS("resources/beat.mp3");
    if (game->gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        // success = false;
    }

    // solveMazeUtil(maze, EnemyInitialX / SIZE, EnemyInitialY / SIZE, MazeSol);

    Mix_PlayMusic(game->gMusic, -1);
}




int main(int args, char *argv[])
{

    game = new Game();

    game->init("Maze game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

    SOUND();

    TTF_Font *font = TTF_OpenFont("resources/font.ttf", 40);
    TTF_Font *font1 = TTF_OpenFont("resources/font1.ttf", 40);


    // SDL_Surface *screen, *icon;
    // const int width = 640;
    // const int height = 480;
    // const int FPS = 30;
    // screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

    while (true)
    {
        int i = showmenu(600, 400, game->renderer, font);

        if (i == 2)
        {
            game->isRunning = false;
            break;
        }

        else if (i == 1)
        {
            int j = soundmenu(600, 400, game->renderer, font);

            if (j == 0)
            {
                // sound ON

                // If the music is paused
                if (Mix_PausedMusic() == 1)
                {
                    // Resume the music
                    Mix_ResumeMusic();
                }
            }

            else if (j == 1)
            {
                // sound OFF

                // If the music is not paused
                if (Mix_PausedMusic() != 1)
                {
                    Mix_PauseMusic();
                }
            }

            else if (j == 2)
            {
                game->isRunning = false;
                break;
            }
        }

        else if (i == 0)
        {
            break;
        }
    }

    game->clean();

    if (game->running())
    {
        game->init("Maze game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    }

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();

        game->timeshow(font1);
        game->health();
        game->restaurant();

        if(game->istext){
            game->boost();
        }

        game->EnemyHandleUpdateRender();


        if (game->isWON)
        {
            // cout << "won" << endl;

            break;
        }

        if (game->isLOSS)
        {
            // cout << "lost" << endl;

            break;
        }
    }

    game->clean();

    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_Window *window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // SDL_RenderClear(renderer);

    // SDL_RenderPresent(renderer);

    // SDL_Delay(3000);

    return 0;
}