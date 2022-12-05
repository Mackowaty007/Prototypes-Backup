#pragma once

void setTheObjectScale(){
	for (int i=0;i<LEN(vertecies);i++){
		for (int c=0;c<LEN(vertecies[0]);c++){
			vertecies[i][c] *= -100;
		}
	}
}

//should have done this in the converter file but text operations are hard
void decrementAllTheVerteciesValuesByOne(){
	for (int i=0;i<LEN(polygons);i++){
		for (int c=0;c<LEN(polygons[0]);c++){
			polygons[i][c] --;
		}
	}
}

float cutANumber(float number,float max,float min){
	if (number>max){
		number=max;
	}
	if (number<min){
		number=min;
	}
	return number;
}

void handleInput(){
	SDL_Event ev;
	SDL_PumpEvents();
	keyboard = SDL_GetKeyState(NULL);
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	SDL_GetMouseState(&mouseX,&mouseY);
	
    while( SDL_PollEvent( &ev ) )
    {
		//quit and stuff
        if( ( SDL_QUIT == ev.type ) ||
            ( SDL_KEYDOWN == ev.type && SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode ) )
        {
            running = false;
            break;
        }

		//rotate the player
		playerRot[0] -= rotSpeed*(oldMouseX-mouseX);//*deltaTime;
		//playerRot[1] += rotSpeed*(oldMouseY-mouseY);//*deltaTime;

		playerRot[1] = cutANumber(playerRot[1],PI,0);
		if(playerRot[0]>PI){
			playerRot[0] -= 2*PI;
		}
		if(playerRot[0]<-PI){
			playerRot[0] += 2*PI;
		}
		if(playerRot[1]>PI){
			playerRot[1] -= 2*PI;
		}
		if(playerRot[1]<-PI){
			playerRot[1] += 2*PI;
		}

		//move the player	
		if(key_map[SDL_SCANCODE_W]){
			playerPos[0] += sin(playerRot[0])*playerSpeed;//*deltaTime;
			playerPos[2] += cos(playerRot[0])*playerSpeed;//*deltaTime;
		}
		if(key_map[SDL_SCANCODE_S]){
			playerPos[0] -= sin(playerRot[0])*playerSpeed;//*deltaTime;
			playerPos[2] -= cos(playerRot[0])*playerSpeed;//*deltaTime;
		}
		if(key_map[SDL_SCANCODE_A]){
			playerPos[0] += sin(playerRot[0]+PI/2)*playerSpeed;//*deltaTime;
			playerPos[2] += cos(playerRot[0]+PI/2)*playerSpeed;//*deltaTime;
		}
		if(key_map[SDL_SCANCODE_D]){
			playerPos[0] -= sin(playerRot[0]+PI/2)*playerSpeed;//*deltaTime;
			playerPos[2] -= cos(playerRot[0]+PI/2)*playerSpeed;//*deltaTime;
		}
		if(key_map[SDL_SCANCODE_LCTRL]){
			playerPos[1] += playerSpeed;//*deltaTime;
		}
		if(key_map[SDL_SCANCODE_SPACE]){
			playerPos[1] -= playerSpeed;//*deltaTime;
		}
    }
}