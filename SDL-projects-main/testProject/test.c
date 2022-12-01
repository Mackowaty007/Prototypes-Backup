#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <math.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define POINT_SIZE 3
#define LINE_WIDTH 1
#define PI 3.1415926535
//smaller number - more FOV
#define FOV 200
#define DRAWING_DISTANCE 500

//#define DRAW_VERTECIES
//#define DRAW_LINES
#define DRAW_FACES

float playerPos[3] = {0,0,-100};
float cameraPos[3] = {0,0,0};
float playerRot[2] = {0,PI/2};
float playerSpeed = 0.01;
float rotSpeed = 0.1;

#include "shape.h"

struct timeval begin, end;
double deltaTime;

#include "usefullPublicFunctions.h"

int main( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    const std::vector< SDL_Vertex > verts =
    {
        { SDL_FPoint{ 400, 150 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ 200, 450 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ 600, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
    };

    bool running = true;
    while( running )
    {
        SDL_Event ev;
        while( SDL_PollEvent( &ev ) )
        {
            if( ( SDL_QUIT == ev.type ) ||
                ( SDL_KEYDOWN == ev.type && SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode ) )
            {
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );
        SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
        SDL_RenderPresent( renderer );
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
    
    return 0;
}
