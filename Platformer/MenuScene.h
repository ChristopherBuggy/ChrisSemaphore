#ifndef MENUSCENE_H
#define MENUSCENE_H
using namespace std;
#include<iostream>
#include<SDL.h>
#include<Render.h>

class MenuScene
{
private:

public:

	MenuScene(int x, int y,Render* renderer);
	SDL_Rect* playRect1;
	SDL_Rect* quitRect1;
	SDL_Surface * quit1;
	SDL_Surface * play1;
	
	SDL_Rect* playRect2;
	SDL_Rect* quitRect2;
	SDL_Surface * quit2;
	SDL_Surface * play2;

	//Shitty Background 
	SDL_Rect* backGroundRect;
	SDL_Surface * back;
	std::string bgPath;

	std::string playPath1;
	std::string quitPath1;

	std::string playPath2;
	std::string quitPath2;

	int current;
	bool quitBool;
	bool playBool;

	bool drawStuff;

	void Update(Render* renderer);
};

#endif
