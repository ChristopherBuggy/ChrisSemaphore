#include "Player.h"
#include <vector>

static const float SCALE = 30.f;

Player::Player(float x, float y, b2World& World, Render* renderer)
{
	world = &World;

	initX = x;
	initY = y;

	rewind = false;

	rewindReset = false;

	SDL_Surface * sprite;
	SDL_Surface * LeftImage;
	SDL_Surface * RightImage;
	SDL_Surface * StandImage;
	SDL_Surface * BlankImage;

	count = 0;

	std::string basepath(SDL_GetBasePath());

	std::string imagePath = basepath + "square.bmp";
	imagePath = basepath + "leftanim.bmp";
	LeftImage = SDL_LoadBMP(imagePath.c_str());
	LeftTexture = SDL_CreateTextureFromSurface(renderer->ren, LeftImage);
	imagePath = basepath + "rightanim.bmp";
	RightImage = SDL_LoadBMP(imagePath.c_str());
	RightTexture = SDL_CreateTextureFromSurface(renderer->ren, RightImage);
	imagePath = basepath + "standstillanim.bmp";
	StandImage = SDL_LoadBMP(imagePath.c_str());
	StandTexture = SDL_CreateTextureFromSurface(renderer->ren, StandImage);/*
	imagePath = basepath + "blankanim.bmp";
	BlankImage = SDL_LoadBMP(imagePath.c_str());
	BlankTexture = SDL_CreateTextureFromSurface(renderer->ren, BlankImage);
	spriteRect = SDL_Rect();
	int iW, iH;
	SDL_QueryTexture(BlankTexture, NULL, NULL, &iW, &iH);*/
	SDL_Rect rec;
	rec.x = x;
	rec.y = y;
	rec.w = 20;
	rec.h = 40;
	spriteRect = rec;
	
	imagePath = basepath + "clock.bmp";
	sprite = SDL_LoadBMP(imagePath.c_str());
	clockRect = renderer->AddSurfaceToRenderer(sprite, -1000, -1000, 0.5f);

	CreateBody();
	deathSound = Mix_LoadWAV((basepath + "death.wav").c_str());
	jumpSound = Mix_LoadWAV((basepath + "jump.wav").c_str());
}


void Player::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(initX / SCALE, initY / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = "Player";
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(true);
	Body->SetSleepingAllowed(false);
	Body->SetGravityScale(3.0f);

	b2PolygonShape Shape;
	Shape.SetAsBox((20 / 2) / SCALE, (40 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);

	playerBody = Body;
}

int Player::Move(InputHandler & input, SDL_Event & e)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	int dir;

	dir = 0;

	if (rewind == false)
	{
		if (keys[SDL_SCANCODE_A]) {
			playerBody->SetTransform(b2Vec2(playerBody->GetPosition().x - 0.15, playerBody->GetPosition().y), 0);
			dir = 1;
			moving = true;
		}

		if (keys[SDL_SCANCODE_D]) {
			playerBody->SetTransform(b2Vec2(playerBody->GetPosition().x + 0.15, playerBody->GetPosition().y), 0);
			dir = 2;
			moving = true;
		}
		if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A])
		{
			moving = false;
		}
		if (keys[SDL_SCANCODE_SPACE]) {
			if (jump == false)
			{
				Mix_PlayChannel(-1, jumpSound, 0);
				playerBody->ApplyLinearImpulse(b2Vec2(0, -143), b2Vec2(0, 0), false);
				jump = true;
			}
		}
	}

	if (keys[SDL_SCANCODE_R]) {
		if (count == 119 && rewindReset == false)
		{
			rewind = true;
			rewindReset = true;
		}
	}
	else
	{
		rewind = false;
	}

	if (jump == true)
	{
		jumpTimer--;
	}
	if (jumpTimer == 0)
	{
		jump = false;
		jumpTimer = 50;
	}

	spriteRect.x = playerBody->GetPosition().x * SCALE;
	//spriteRect->y = playerBody->GetPosition().y * SCALE;
	y = (playerBody->GetPosition().y * SCALE) + 5;

	if (count == 119 && rewindReset == false)
	{
		clockRect->x = -1000;
		clockRect->y = -1000;
	}
	else
	{
		clockRect->x = -1000;
		clockRect->y = -1000;
	}

	if (rewind == false)
	{
		if (rewindReset == true)
		{
			prevPosX.clear();
			prevPosY.clear();
			count = 0;
			rewindReset = false;
		}
	}

	if (rewind == false)
	{
		if (prevPosX.size() < 120)
		{
			prevPosX.push_back(spriteRect.x);
		}
		else
		{
			prevPosX.erase(prevPosX.begin());
			prevPosX.push_back(spriteRect.x);
		}
		if (prevPosY.size() < 120)
		{
			prevPosY.push_back(y);
		}
		else
		{
			prevPosY.erase(prevPosY.begin());
			prevPosY.push_back(y);
		}

		if (count < 119)
		{
			count++;
		}
	}

	if (rewind == true)
	{
		if (count > 0)
		{
			if (prevX == prevPosX.at(count - 1))
			{
				dir = 0;
			}
			if (prevX > prevPosX.at(count - 1))
			{
				dir = 1;
			}
			if (prevX < prevPosX.at(count - 1))
			{
				dir = 2;
			}
			prevX = prevPosX.at(count - 1);
			spriteRect.x = prevPosX.at(count - 1);
			y = prevPosY.at(count - 1);
			playerBody->SetTransform(b2Vec2(spriteRect.x / SCALE, spriteRect.y / SCALE), 0);
			count--;
		}
	}

	if (spriteRect.y > 820)
	{
		Respawn();
	}
	if (spriteRect.y < -100)
	{
		Respawn();
	}
	if (spriteRect.x > 1380)
	{
		Respawn();
	}
	if (spriteRect.x < -100)
	{
		Respawn();
	}
	return dir;
}
void Player::Respawn() //Respawn Method
{
	b2Vec2 pos((initX + 80) / SCALE, initY / SCALE);
	playerBody->SetTransform(pos, 0);
	Mix_PlayChannel(-1, deathSound, 0);
}


int Player::GetY() const
{
	return y;
}