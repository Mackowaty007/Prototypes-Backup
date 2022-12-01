// Simple citro2d untextured shape example
#include <3ds.h>
#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240
#define BOT_SCREEN_WIDTH  320
#define BOT_SCREEN_HEIGHT 240
#define POINT_SIZE 3
#define LINE_WIDTH 0.6
#define PI 3.1415926535
//smaller number - more FOV
#define FOV 200
#define DRAWING_DISTANCE 500

#define DEBUG_MODE//shows the console
#define DISSABLE_THE_3D_MODE
#define DRAW_VERTECIES
#define DRAW_LINES
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

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(LEN(polygons)*4*2);
	C2D_Prepare();
	#ifdef DEBUG_MODE
	consoleInit(GFX_BOTTOM, NULL);
	#endif

	// Create screens
	C3D_RenderTarget* left = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* right =C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
	#ifndef DEBUG_MODE
	C3D_RenderTarget* down = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	#endif

	gfxSet3D(true);
	setTheObjectScale();
	decrementAllTheVerteciesValuesByOne();

	// Create colors
	u32 clrClear   = C2D_Color32(0x1F, 0x10, 0x0F, 0xFF);
    u32 vertexColor= C2D_Color32(0xF0, 0x1F, 0x0F, 0xFF);
	u32 playerColor= C2D_Color32(0xDE, 0xAD, 0xBE, 0xFF);
	u32 lineColor  = C2D_Color32(0x0F, 0XFA, 0x1A, 0xFF);
	u32 polygonColor=C2D_Color32(0x0F, 0X3A, 0xFA, 0xFF);

	// Main loop
	while (aptMainLoop())
	{
		#ifdef DEBUG_MODE
		//consoleClear();
		#endif

		handleInput();

		#include "display.h"

		//get performance data
		printf("\x1b[22;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[23;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[24;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);
	}

	exitTheGame();
	return 0;
}
