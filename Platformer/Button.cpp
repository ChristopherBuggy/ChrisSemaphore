#include "Button.h"
static const float SCALE = 30.f;

Button::Button(float x, float y, b2World& World, Render* renderer)
{
	world = &World;

	initX = x;
	initY = y;
	collision = false;

	onlyOnce = false;

	SDL_Surface * sprite;

	std::string basepath(SDL_GetBasePath());

	std::string imagePath = basepath + "Leader.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = renderer->AddSurfaceToRenderer(sprite, initX, initY, 0.5f);
	CreateBody();
}

void Button::Update()
{
	spriteRect->x = ((buttonBody->GetPosition().x) * SCALE + 13);
	spriteRect->y = ((buttonBody->GetPosition().y) * SCALE);
}

bool Button::CheckCollision(SDL_Rect* playerRect)
{
	if (onlyOnce == false)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = spriteRect->x;
		rightA = spriteRect->x + spriteRect->w;
		topA = spriteRect->y;
		bottomA = spriteRect->y + spriteRect->h;

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
		onlyOnce = true;
		return true;
	}
	return false;
}


void Button::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(initX / SCALE, initY / SCALE);
	BodyDef.type = b2_staticBody;
	BodyDef.userData = "Button";
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(true);
	Body->SetSleepingAllowed(false);
	Body->SetGravityScale(3.0f);

	b2PolygonShape Shape;
	Shape.SetAsBox((26.5 / 2) / SCALE, (25.5 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	//FixtureDef.isSensor = true;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	//Body->CreateFixture(&FixtureDef);

	buttonBody = Body;
}

void Button::setOnce(bool b)
{
	onlyOnce = b;
}

