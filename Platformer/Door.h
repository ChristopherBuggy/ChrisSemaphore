#ifndef DOOR_H
#define DOOR_H
using namespace std;
#include<iostream>
#include<SDL.h>
#include "Render.h"

class Door
{
private:

	float initX = 0;
	float initY = 0;
	float initX1 = 0;
	float initY1 = 0;


public:
	Door(float x, float y, Render* renderer);
	SDL_Surface * sprite;
	SDL_Rect* spriteRect;
	SDL_Surface * sprite1;
	SDL_Rect* spriteRect1;
	bool open = false;
	void DrawCage(Render* renderer);
	void DrawNoCage(Render* renderer);
	bool CheckCollision(SDL_Rect* playerRect);
};

#endif
