#pragma once
#ifndef CANNON_H
#define CANNON_H
 
using namespace std;
#include<iostream>
#include<Box2D\Box2D.h>
#include<SDL.h>
#include "Render.h"
#include "Fireball.h"

class Cannon
{
public:
	Cannon(float x, float y, b2World& World, Render* renderer, float dir);
	void Update();
	vector<Fireball*> fireballs;

private:
	SDL_Surface * sprite;
	float initX = 0;
	float initY = 0;
	SDL_Rect* spriteRect;
	float dir;


};

#endif

