#include "Door.h"
static const float SCALE = 30.f;

Door::Door(float x, float y, Render* renderer)
{
	initX = x;
	initY = y;
	initX1 = 100000;
	initY1 = 100000;

	std::string basepath(SDL_GetBasePath());
	std::string imagePath = basepath + "door.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = renderer->AddSurfaceToRenderer(sprite, -1000, -1000, 0.5f);

	std::string imagePath1 = basepath + "door1.bmp";
	sprite1 = SDL_LoadBMP(imagePath1.c_str());
	spriteRect1 = renderer->AddSurfaceToRenderer(sprite1, -1000, -1000, 0.5f);
}

bool Door::CheckCollision(SDL_Rect* playerRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = spriteRect1->x;
	rightA = spriteRect1->x + spriteRect1->w;
	topA = spriteRect1->y;
	bottomA = spriteRect1->y + spriteRect1->h;

	//Calculate the sides of rect B
	leftB = playerRect->x;
	rightB = playerRect->x + playerRect->w;
	topB = playerRect->y;
	bottomB = playerRect->y + playerRect->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Door::DrawCage(Render* renderer)
{
	spriteRect->x = 990;
	spriteRect->y = 19;
	spriteRect1->x = 1000000;
	spriteRect1->y = 1000000;
}
void Door::DrawNoCage(Render* renderer)
{
	spriteRect1->x = 990;
	spriteRect1->y = 19;
	spriteRect->x = 1000000;
	spriteRect->y = 1000000;
}