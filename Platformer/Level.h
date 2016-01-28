#ifndef LEVEL_H
#define LEVEL_H
using namespace std;
#include<iostream>
#include "Render.h"
#include "Platform.h"

class Level
{
private:

public:
	Level(b2World& World, Render* renderer);
	Platform* platforms[30];
};


#endif