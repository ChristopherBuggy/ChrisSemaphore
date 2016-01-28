#pragma once
#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
#include<iostream>
#include<Box2D\Box2D.h>
#include<SDL.h>
#include<InputHandler.h>
#include<Render.h>
#include <SDL_mixer.h>

class Player
{
private:
	b2World* world;
	b2Body* playerBody;

	float initX = 0;
	float initY = 0;
	float y = 0;

	SDL_Rect* clockRect;

	bool jump = false;
	int jumpTimer = 50;

	bool rewind;

	bool rewindReset;

	float prevX;
	Mix_Chunk *deathSound = NULL;
	Mix_Chunk *jumpSound = NULL;

//=======
//>>>>>>> 3c2d0afd728d7c78049d0b24333aee5088a5a6a8
public:
	Player(float x, float y, b2World& World, Render* renderer);

	SDL_Rect spriteRect;
	SDL_Rect dstRect;
	SDL_Rect srcRect;
	SDL_Texture* LeftTexture;
	SDL_Texture* RightTexture;
	SDL_Texture* StandTexture;
	SDL_Texture* BlankTexture;

	vector<float> prevPosX;
	vector<float> prevPosY;

	int count;

	bool moving;
	int GetY() const;
	void CreateBody();

	int Move(InputHandler & input, SDL_Event & e);

	void Draw(SDL_Renderer *ren, SDL_Texture *, SDL_Rect imageRect);

	void Respawn();

	//The "data buffer"
	int gData = -1;
};


#endif