#include "Game.hpp"
#include "path.hpp"
using namespace std;

Game::Game(/* args */)
{
}

Game::~Game()
{
}

class BackGround
{
public:
    SDL_Surface *bgSurface = NULL;
    SDL_Texture *bgTexture = NULL;
    SDL_Color rgb;
};

BackGround *bg = nullptr;

SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer)
{
    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0; /* shouldn't happen, but avoids warnings */
    }
}

bool checkCollision(SDL_Rect playerRect, SDL_Surface *surface)
{
    // The sides of the rectangles
    // int leftA;
    // int rightA;
    // int topA;
    // int bottomA;

    // Calculate the sides of rect A
    // leftA = playerRect.x;
    int X = playerRect.x;
    // topA = playerRect.y;
    int Y = playerRect.y;

    // if (mazeList[playerRect.y / playerRect.h][playerRect.x / playerRect.w] == 1)
    // {
    //     return true;
    // }

    // If none of the sides from A are outside B
    // return false;

    int tempSIZE = 6;

    for (int i = X - tempSIZE; i < X + tempSIZE + 1; i++)
    {
        for (int j = Y - tempSIZE; j < Y + tempSIZE + 1; j++)
        {

            if (i - 10 < 0 || i > LEVEL_WIDTH)
            {
                return true;
            }

            if (j - 10 < 0 || j - 0 > LEVEL_HEIGHT)
            {
                return true;
            }
            Uint32 data = getpixel(surface, i, j);

            SDL_Color rgb1 = bg->rgb;

            SDL_GetRGB(data, surface->format, &rgb1.r, &rgb1.g, &rgb1.b);

            if ((rgb1.r == 0xFF) && (rgb1.g == 0xFF) && (rgb1.b == 0xFF))
            {
                return false;
            }
        }
    }

    // Uint32 data = getpixel(surface, X, Y);

    // SDL_Color rgb1 = bg->rgb;

    // SDL_GetRGB(data, surface->format, &rgb1.r, &rgb1.g, &rgb1.b);

    // if ((rgb1.r == 0xFF) && (rgb1.g == 0xFF) && (rgb1.b == 0xFF))
    // {
    //     return false;
    // }

    return true;
}

// bool checkCollision(int mazeList[MAZE_ROW][MAZE_COLUMN], SDL_Rect a)
// {
//     // The sides of the rectangles
//     int leftA;
//     int rightA;
//     int topA;
//     int bottomA;

//     // Calculate the sides of rect A
//     leftA = a.x;
//     rightA = a.x + a.w;
//     topA = a.y;
//     bottomA = a.y + a.h;

//     if (mazeList[a.y / a.h][a.x / a.w] == 1)
//     {
//         return true;
//     }

//     // If none of the sides from A are outside B
//     return false;
// }

// class cell
// {
//     public:
//         static const int CELL_SIZE = 20;

//         int Xpos;
//         int Ypos;

//         cell* right;
//         cell* left;
//         cell* up;
//         cell* down;

//         int CELL_TYPE;  // 1 for white
//                         // 0 for black

//     private:

// };

// void buildMaze(int camX, int camY, int mazeList[MAZE_ROW][MAZE_COLUMN], int row, int col, SDL_Renderer *renderer, int DestX, int DestY)
// {
//     int size = SIZE;

//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < col; j++)
//         {
//             if (mazeList[i][j] == 1)
//             {
//                 SDL_Rect rect;
//                 rect.x = size * (j)-camX;
//                 rect.y = size * (i)-camY;
//                 rect.w = size;
//                 rect.h = size;

//                 // cell* newCELL = new cell;

//                 // newCELL -> CELL_TYPE = 0;

//                 // if(i==0 && j==0){
//                 //     newCELL -> right =
//                 // }

//                 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//                 SDL_RenderFillRect(renderer, &rect);
//             }

//             if (i == DestX && j == DestY)
//             {
//                 SDL_Rect rect;
//                 rect.x = size * (j)-camX;
//                 rect.y = size * (i)-camY;
//                 rect.w = size;
//                 rect.h = size;

//                 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//                 SDL_RenderFillRect(renderer, &rect);
//             }
//         }
//     }
// }

// A utility function to check if x, y is valid index for
// N*N maze
// bool isSafe(int maze[MAZE_ROW][MAZE_COLUMN], int x, int y)
// {
//     // if (x, y outside maze) return false
//     if (x >= 0 && x < MAZE_ROW && y >= 0 && y < MAZE_COLUMN && maze[x][y] == 0)
//     {
//         return true;
//     }
//     return false;
// }

// // A recursive utility function to solve Maze problem
// bool solveMazeUtil(int maze[MAZE_ROW][MAZE_COLUMN], int x, int y, int sol[MAZE_ROW][MAZE_COLUMN])
// {
//     // if (x, y is goal) return true
//     if (x == DestX && y == DestY && maze[x][y] == 0)
//     {
//         sol[x][y] = 1;
//         return true;
//     }
//     // Check if maze[x][y] is valid
//     if (isSafe(maze, x, y) == true)
//     {
//         // Check if the current block is already part of
//         // solution path.
//         if (sol[x][y] == 1)
//             return false;
//         // mark x, y as part of solution path
//         sol[x][y] = 1;
//         /* Move forward in x direction */
//         if (solveMazeUtil(maze, x + 1, y, sol) == true)
//             return true;
//         // If moving in x direction doesn't give solution
//         // then Move down in y direction
//         if (solveMazeUtil(maze, x, y + 1, sol) == true)
//             return true;

//         if (solveMazeUtil(maze, x - 1, y, sol) == true)
//             return true;

//         if (solveMazeUtil(maze, x, y - 1, sol) == true)
//             return true;

//         // If none of the above movements work then
//         // BACKTRACK: unmark x, y as part of solution path
//         sol[x][y] = 0;
//         return false;
//     }
//     return false;
// }

void loadFinishImg(int x, int y, SDL_Texture *gTexture, SDL_Renderer *renderer)
{
    SDL_Rect *clip = NULL;
    double angle = 0.0;
    SDL_Point *center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_Rect renderQuad = {DestX - x, DestY - 50 - y, 50, 60};

    // cout << mPosX << "__" << mPosY << endl;

    // Set clip rendering dimensions
    // if (clip != NULL)
    // {
    //     renderQuad.w = clip->w;
    //     renderQuad.h = clip->h;
    // }

    // Render to screen
    SDL_RenderCopyEx(renderer, gTexture, clip, &renderQuad, angle, center, flip);
}

void bgRender(int x, int y, SDL_Texture *gTexture, SDL_Renderer *renderer)
{
    SDL_Rect *clip = NULL;
    double angle = 0.0;
    SDL_Point *center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_Rect renderQuad = {5 - x, 5 - y, LEVEL_WIDTH, LEVEL_HEIGHT};

    // cout << mPosX << "__" << mPosY << endl;

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(renderer, gTexture, clip, &renderQuad, angle, center, flip);
}

class Dot
{
public:
    // The dimensions of the dot
    int DOT_WIDTH;
    int DOT_HEIGHT;

    // Maximum axis velocity of the dot
    static const int DOT_VEL = 1;

    // Initializes the variables
    Dot(int x, int y, int w, int h);

    // Takes key presses and adjusts the dot's velocity
    void handleEventForPlayer(SDL_Event &e);

    void handleEventForEnemy();

    // Moves the dot
    void move();

    void moveforEnemy();

    // Shows the dot on the screen
    void render(int x, int y, SDL_Texture *gTexture, SDL_Renderer *renderer);

    // The X and Y offsets of the dot
    int mPosX, mPosY;

    // Only used for enemy
    // int PreviousPosX, PreviousPosY;
    int idx;

private:
    // cell CELL;

    // The velocity of the dot
    int mVelX, mVelY;

    // Dot's collision box
    SDL_Rect mCollider;

    bool TEMP = false;
};

Dot::Dot(int x, int y, int w, int h)
{
    // Initialize the offsets
    mPosX = x;
    mPosY = y;

    DOT_WIDTH = w;
    DOT_HEIGHT = h;

    idx = 0;

    // Set collision box dimension
    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;

    // Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEventForPlayer(SDL_Event &e)
{
    // If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        TEMP = true;

        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY += DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += DOT_VEL;
            break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY -= DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX += DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= DOT_VEL;
            break;
        }
    }
}

void Dot::handleEventForEnemy()
{
    // int j = mPosX / SIZE;
    // int i = mPosY / SIZE;

    string list[] = level1;

    if (idx < 795)
    {

        // TEMP = true;

        if (list[idx] == "D")
        {
            mVelY = DOT_VEL;
            // cout << i << "__" << j << "__" << 1 << endl;
        }
        else if (list[idx] == "R")
        {
            mVelX = DOT_VEL;
            // cout << i << "__" << j << "__" << 2 << endl;
        }
        else if (list[idx] == "U")
        {
            mVelY = -1 * DOT_VEL;
            // cout << i << "__" << j << "__" << 3 << endl;
        }
        else if (list[idx] == "L")
        {
            mVelX = -1 * DOT_VEL;
            // cout << i << "__" << j << "__" << 4 << endl;
        }

        idx++;
    }
    // cout << idx << endl;
}

void Dot::move()
{
    // if (TEMP)
    // {
    //     TEMP = false;

    // bool b1 = true;
    // bool b2 = true;

    // Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;

    // If the dot collided or went too far to the left or right
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > LEVEL_WIDTH) || checkCollision(mCollider, bg->bgSurface))
    {
        // Move back
        // b1 = false;

        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    // Move the dot up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    // If the dot collided or went too far up or down
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > LEVEL_HEIGHT) || checkCollision(mCollider, bg->bgSurface))
    {
        // Move back
        // b2 = false;

        mPosY -= mVelY;
        mCollider.y = mPosY;
    }

    // if(mVelX > 0 && b1){
    //     cout << "R";
    // }
    // else if(mVelX < 0 && b1) {
    //     cout << "L";
    // }

    // if(mVelY > 0 && b2){
    //     cout << "D";
    // }
    // else if(mVelY < 0 && b2) {
    //     cout << "U";
    // }

    // }
}

void Dot::moveforEnemy()
{
    // TEMP = false;

    // Move the dot left or right
    // PreviousPosX = mPosX;

    mPosX += mVelX;
    mCollider.x = mPosX;

    mVelX = 0;

    // If the dot collided or went too far to the left or right
    // if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(mazeList, mCollider))
    // {
    //     // Move back
    //     mPosX -= mVelX;
    //     mCollider.x = mPosX;
    // }

    // Move the dot up or down
    // PreviousPosY = mPosY;

    mPosY += mVelY;
    mCollider.y = mPosY;

    mVelY = 0;

    // If the dot collided or went too far up or down
    // if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(mazeList, mCollider))
    // {
    //     // Move back
    //     mPosY -= mVelY;
    //     mCollider.y = mPosY;
    // }

    // SDL_Delay(1000);
}

void Dot::render(int x, int y, SDL_Texture *gTexture, SDL_Renderer *renderer)
{
    // Show the dot
    // gDotTexture.render( mPosX, mPosY );

    SDL_Rect *clip = NULL;
    double angle = 0.0;
    SDL_Point *center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_Rect renderQuad = {mPosX - x - 13, mPosY - y - DOT_HEIGHT + 6, DOT_WIDTH, DOT_HEIGHT};

    // cout << mPosX << "__" << mPosY << endl;

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(renderer, gTexture, clip, &renderQuad, angle, center, flip);
}

Dot dot(PlayerInitialX, PlayerInitialY, 50, 60);
Dot enemy(EnemyInitialX, EnemyInitialY, 40, 60);

// dot = new Dot();

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // SDL_Rect rect;
    // rect.x = 30;
    // rect.y = 40;
    // rect.w = 150;
    // rect.h = 100;

    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = 479;
    SrcR.h = 479;

    DestR.x = 0;
    DestR.y = 0;
    DestR.w = SIZE;
    DestR.h = SIZE;

    bg = new BackGround();

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // cout << "Subsystem Initialied..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        {
            // cout << "Window Created!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {

            // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            // SDL_RenderClear( renderer );

            // SDL_RenderPresent(renderer);

            // cout << "Renderer Created!" << endl;

            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }

            playerTexture = loadTexture("resources/player1.png", renderer);
            if (playerTexture == NULL)
            {
                cout << "Failed to load player texture image!" << endl;
            }

            enemyTexture = loadTexture("resources/enemy.png", renderer);
            if (enemyTexture == NULL)
            {
                cout << "Failed to load enemy texture image!" << endl;
            }

            finishTexture = loadTexture("resources/finish.png", renderer);
            if (finishTexture == NULL)
            {
                cout << "Failed to load finish texture image!" << endl;
            }

            // bgTexture = loadTexture("resources/map.jpg", renderer);

            bg->bgSurface = IMG_Load("resources/map.png");
            bg->bgTexture = SDL_CreateTextureFromSurface(renderer, bg->bgSurface);

            if (bg->bgTexture == NULL)
            {
                cout << "Failed to load map texture image!" << endl;
            }

            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                // success = false;
            }

            // SDL_RenderCopy(renderer, playerTexture, &SrcR, &DestR);
            // SDL_RenderPresent(renderer);

            // for (int i = 0; i < MAZE_ROW; i++) {
            //     for (int j = 0; j < MAZE_COLUMN; j++){
            //         cout << " " << MazeSol[i][j] << " ";
            //     }
            //     cout << endl;
            // }

            // enemyList[0] = 2;
        }

        isRunning = true;
    }

    else
    {
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    // SDL_PollEvent(&event);

    // switch (event.type) {
    // case SDL_QUIT:
    //     isRunning = false;
    //     break;

    // default:
    //     break;
    // }

    while (SDL_PollEvent(&event) != 0)
    {

        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            }
        }

        int x = 8;
        int y = 8;


        bool b1 = 775 - x <= dot.mPosX && dot.mPosX <= 775 + x && 375 - y <= dot.mPosY && dot.mPosY <= 375 + y;
        bool b2 = 345 - x <= dot.mPosX && dot.mPosX <= 345 + x && 320 - y <= dot.mPosY && dot.mPosY <= 320 + y;
        bool b3 = 610 - x <= dot.mPosX && dot.mPosX <= 610 + x && 255 - y <= dot.mPosY && dot.mPosY <= 255 + y;
        bool b4 = 1310 - x <= dot.mPosX && dot.mPosX <= 1315 + x && 280 - y <= dot.mPosY && dot.mPosY <= 285 + y;
        bool b5 = 1345 - x <= dot.mPosX && dot.mPosX <= 1360 + x && 435 - y <= dot.mPosY && dot.mPosY <= 440 + y;

        // SDL_Texture *text = loadTexture("resources/text.png", renderer);


        if(b1 || b2 || b3 || b4 || b5){


            istext = true;
            // SDL_Rect rect = {200, 320, 150, 60};
            // SDL_RenderCopyEx(renderer, text, NULL, &rect, 0.0, NULL, SDL_FLIP_NONE);
            // SDL_RenderPresent(renderer);

            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                    healthStatus = 6;
                    break;
                }
            }
        }
        else{
            istext = false;
        }

        

        // cout << "poll event" << endl;

        dot.handleEventForPlayer(event);
    }

    // enemy.handleEventForEnemy(MazeSol);
}

void Game::update()
{
    // cout << "update" << endl;

    // dot.move(maze);
    // enemy.moveforEnemy();

    if (playerSlow == playerSpeed)
    {
        dot.move();

        playerSlow = 0;
    }

    else
    {
        playerSlow++;
    }
}

void Game::render()
{

    // cout << "render" << endl;

    // SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
    SDL_RenderClear(renderer);

    // Render wall
    // SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    // SDL_RenderFillRect(renderer, &rect);

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Center the camera over the dot
    camera.x = (dot.mPosX + dot.DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (dot.mPosY + dot.DOT_HEIGHT) - SCREEN_HEIGHT / 2;

    // Keep the camera in bounds
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }

    // buildMaze(camera.x, camera.y, maze, MAZE_ROW, MAZE_COLUMN, renderer, DestX, DestY);

    bgRender(camera.x, camera.y, bg->bgTexture, renderer);

    loadFinishImg(camera.x, camera.y, finishTexture, renderer);

    dot.render(camera.x, camera.y, playerTexture, renderer);
    // enemy.render(enemyTexture, renderer);
    // SDL_RenderPresent(renderer);

    if (DestX - 2 <= dot.mPosX && dot.mPosX <= DestX + 2 && DestY - 2 <= dot.mPosY && dot.mPosY <= DestY + 2)
    {
        enemy.render(camera.x, camera.y, enemyTexture, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        isWON = true;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Congratulations", "You won the match!", NULL);
    }

    if (DestX - 2 <= enemy.mPosX && enemy.mPosX <= DestX + 2 && DestY - 2 <= enemy.mPosY && enemy.mPosY <= DestY + 2)
    {
        SDL_Delay(500);
        isLOSS = true;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Oops", "Better luck next time!", NULL);
    }
}

void Game::EnemyHandleUpdateRender()
{

    if (slow == enemySpeed)
    {
        enemy.handleEventForEnemy();
        enemy.moveforEnemy();

        slow = 0;
    }

    else
    {
        slow++;
    }

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Center the camera over the dot
    camera.x = (dot.mPosX + dot.DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (dot.mPosY + dot.DOT_HEIGHT) - SCREEN_HEIGHT / 2;

    // Keep the camera in bounds
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }

    enemy.render(camera.x, camera.y, enemyTexture, renderer);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Mix_FreeMusic(gMusic);
    // gMusic = NULL;

    // Mix_Quit();
    IMG_Quit();
    // SDL_Quit();
    // cout << "Game cleaned!" << endl;
}

void Game::timeshow(TTF_Font *font)
{
    // int startTime = 0;

    if (isTIMELEFT)
    {

        if (SDL_GetTicks() / 1000 - startTime >= 1) {
            startTime = SDL_GetTicks()/1000;

            if (t1 <= 0) {
                t1 = 59;
            }

            else {
                t1 = t1 - 1;
            }

            if (t1 == 59) {
                t2 = t2 - 1;
            }

            else if (t2 == 0 && t1 == 0) {
                isTIMELEFT = false;
            }
        }

        string s1 = to_string(t1);
        string s2 = to_string(t2);

        

        if(t1 <= 9){
            time = "Time Left  0" + s2 + ":" + "0" + s1;
        }
        else {
            time = "Time Left  0" + s2 + ":" + s1;
        }
        // cout << time << endl;
    }
    // const char *labels = "ON";

    else {
        SDL_Delay(500);
        isLOSS = true;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Oops", "You ran out of time!", NULL);
    }


    timeSurface = TTF_RenderText_Solid(font, time.c_str(), {0, 0, 0});

    int w = 230;
    int h = 40;

    SDL_Rect rect = {10, 2, w, h};

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, timeSurface);

    SDL_RenderCopyEx(renderer, tex, NULL, &rect, 0.0, NULL, SDL_FLIP_NONE);

    // SDL_RenderPresent(renderer);

    
}

void Game::health(){

    if (SDL_GetTicks() / 1000 - t >= 9) {
        t = SDL_GetTicks()/1000;
        healthStatus = healthStatus - 1;
    }

    string s = "resources/health1.png";

    if(healthStatus == 1){
        s = "resources/health1.png";
    }
    if(healthStatus == 2){
        s = "resources/health2.png";
    }
    if(healthStatus == 3){
        s = "resources/health3.png";
    }
    if(healthStatus == 4){
        s = "resources/health4.png";
    }
    if(healthStatus == 5){
        s = "resources/health5.png";
    }
    if(healthStatus == 6){
        s = "resources/health6.png";
    }

    if(healthStatus == 0){
        SDL_Delay(500);
        isLOSS = true;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Oops", "no more Heath!", NULL);
    }

    healthTexture = loadTexture(s, renderer);

    int w = 230;
    int h = 80;
    SDL_Rect rect = {SCREEN_WIDTH - w - 5, 5, w, h};

    SDL_RenderCopyEx(renderer, healthTexture, NULL, &rect, 0.0, NULL, SDL_FLIP_NONE);
}

void Game::restaurant(){

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Center the camera over the dot
    camera.x = (dot.mPosX + dot.DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (dot.mPosY + dot.DOT_HEIGHT) - SCREEN_HEIGHT / 2;

    // Keep the camera in bounds
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }

    SDL_Texture *resTexture = loadTexture("resources/restaurant.png", renderer);
    SDL_Texture *coffeeTexture = loadTexture("resources/coffee.png", renderer);


    SDL_Rect rect1 = {750 - camera.x, 320 - camera.y, 60, 60};
    SDL_RenderCopyEx(renderer, resTexture, NULL, &rect1, 0.0, NULL, SDL_FLIP_NONE);

    SDL_Rect rect2 = {320 - camera.x, 270 - camera.y, 60, 60};
    SDL_RenderCopyEx(renderer, resTexture, NULL, &rect2, 0.0, NULL, SDL_FLIP_NONE);

    SDL_Rect rect3 = {585 - camera.x, 200 - camera.y, 60, 60};
    SDL_RenderCopyEx(renderer, coffeeTexture, NULL, &rect3, 0.0, NULL, SDL_FLIP_NONE);

    SDL_Rect rect4 = {1290 - camera.x, 225 - camera.y, 60, 60};
    SDL_RenderCopyEx(renderer, coffeeTexture, NULL, &rect4, 0.0, NULL, SDL_FLIP_NONE);

    SDL_Rect rect5 = {1330 - camera.x, 380 - camera.y, 60, 60};
    SDL_RenderCopyEx(renderer, resTexture, NULL, &rect5, 0.0, NULL, SDL_FLIP_NONE);
}


void Game::boost(){
    SDL_Texture *text = loadTexture("resources/text.png", renderer);
    SDL_Rect rect = {70, 10, 1077, 111};
    SDL_RenderCopyEx(renderer, text, NULL, &rect, 0.0, NULL, SDL_FLIP_NONE);
    // SDL_RenderPresent(renderer);
}