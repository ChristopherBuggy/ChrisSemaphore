
#include "Platform.h"
#include "Render.h"
#include <iostream>
using namespace std;

static const float SCALE = 30.f;

Platform::Platform(int x1, int y1, int width1, int height1, b2World& World, Render* renderer, int type)
{
	x = x1;
	y = y1;
	width = width1;
	height = height1;
	imageRect.x = x;
	imageRect.y = y;
	imageRect.w = width;
	imageRect.h = height;
	world = &World;

	SDL_Surface * sprite;

	std::string basepath(SDL_GetBasePath());
	if (type == 1) {
		img = "platform.bmp";
	}
	if (type != 1) {
		img = "fullwall.bmp";
	}
	std::string imagePath = basepath + img;
	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = renderer->AddSurfaceToRenderer(sprite, x, y, 1);

	CreateBody();
	if (type == 1) {
		spriteRect->x = ((playerBody->GetPosition().x) * SCALE) - 38;
		spriteRect->y = ((playerBody->GetPosition().y) * SCALE) + 19;
	}

	if (type == 2) {
		spriteRect->x = ((playerBody->GetPosition().x) * SCALE) - 58;
		spriteRect->y = ((playerBody->GetPosition().y) * SCALE) + 19;
	}
}

void Platform::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = world->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(((width) / 2) / SCALE, ((height)) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);

	playerBody = Body;
}

void Platform::Update()
{
	imageRect.x = playerBody->GetPosition().x;
	imageRect.y = playerBody->GetPosition().y;
	imageRect.w = 100;
	imageRect.h = 10;
}


//void Platform::Update()
//{
//	imageRect.x = ((playerBody->GetPosition().x) * SCALE) - 23;
//	imageRect.y = ((playerBody->GetPosition().y) * SCALE) + 19;
//	imageRect.w = 100;
//	imageRect.h = 10;
//}
