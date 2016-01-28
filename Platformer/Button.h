#ifndef ENEMY_H
#define ENEMY_H
using namespace std;
#include<iostream>
#include<Box2D\Box2D.h>
#include<SDL.h>
#include "Render.h"

class Button
{
private:
	b2World* world;
	float initX = 0;
	float initY = 0;
	bool onlyOnce;

public:
	Button(float x, float y, b2World& World, Render* renderer);
	b2Body* buttonBody;
	SDL_Rect* spriteRect;
	void CreateBody();
	bool collision;
	bool CheckCollision(SDL_Rect* playerRect);
	void Update();
	void setOnce(bool b);
};

#endif