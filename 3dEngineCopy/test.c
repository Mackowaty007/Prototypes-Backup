#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <math.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

#define SCREEN_WIDTH  1000
#define SCREEN_HEIGHT 1000
#define POINT_SIZE 3
#define LINE_WIDTH 1
#define PI 3.1415926535
//smaller number - more FOV
#define FOV 200
#define DRAWING_DISTANCE 500

#define DRAW_VERTECIES
#define DRAW_LINES
//#define DRAW_FACES

//is the game running
bool running = true;
//global variables
float playerPos[3] = {0,0,-1};
float playerRot[2] = {0,PI/2};
float playerSpeed = 1.0;
float rotSpeed = 0.001;
int mouseX=0, mouseY=0, oldMouseX, oldMouseY;
const Uint8 *keystates;
//time vars
struct timeval begin, end;
double deltaTime;

#include "shape.h"
#include "usefullPublicFunctions.h"

int main( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    
    setTheObjectScale();
	decrementAllTheVerteciesValuesByOne();

    while( running )
    {
        handleInput();

        //printf("x:%f y:%f z:%f\n",playerPos[0],playerPos[1],playerPos[2]);

        #include "display.h"
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
    
    return 0;
}
