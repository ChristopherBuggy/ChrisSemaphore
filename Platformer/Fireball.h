#pragma once
#ifndef FIREBALL_H
#define FIREBALL_H

using namespace std;
#include<iostream>
#include<Box2D\Box2D.h>
#include<SDL.h>
#include "Render.h"

class Fireball
{
public:
	Fireball(float x, float y, b2World& World, Render* renderer, float dir);
	void Update(int dir);

	void CreateBody();
	void RemoveSurface();
	bool CheckLife();
	bool CheckCollision(SDL_Rect* playerRect);
	b2Body* fireballBody;
	float initX = 0;

	//Thread stuff
	//Our worker functions
	int producer(void* data);
	int consumer(void* data);
	void produce();
	void consume();

	//The protective mutex
	SDL_mutex* gBufferLock = NULL;

	//The conditions
	SDL_cond* gCanProduce = NULL;
	SDL_cond* gCanConsume = NULL;

	//The "data buffer"
	int gData = -1;

private:
	b2World* world;
	SDL_Surface * sprite;
	float dir;
	float initY = 0;

	SDL_Rect* spriteRect;
};

#endif

