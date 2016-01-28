/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <Box2D/Box2D.h>
#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <InputHandler.h>       // Added by Alison
#include <Render.h> //Added by Jonathan
#include <Player.h>
#include <Level.h>
#include <vector>
#include <Fireball.h>
#include <MenuScene.h>
#include <Cannon.h>
#include <Button.h>
#include <Door.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>

static const float SCALE = 30.f;


void logSDLError(const std::string &msg) {
	//std::cout << msg << " error: " << SDL_GetError() << std::endl;
}



int QuitWithError(const std::string &msg) {
	//std::cout << msg << " error: " << SDL_GetError() << std::endl;
	SDL_Delay(1000); //give user a chance to read error
	SDL_Quit();
	return 1;
}

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/

std::vector<b2Vec2> timeArray(60);

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
SDL_Surface* image;
InputHandler inputHandler = InputHandler();
SDL_mutex* mut;
SDL_mutex* mut1;
SDL_Rect* spriteRect;
SDL_Surface * sprite;
SDL_Rect* spriteRect1;
SDL_Surface * sprite1;
SDL_Rect* spriteRect2;

SDL_Surface * newSprite;
SDL_Rect* newRect;

int x = 500;
int y = 650;

int x2 = 350;
int y2 = 650;

int x3 = 150;
int y3 = 650;

int pos;
bool left;
bool right;
int randNum;

//Implmentation of Semaphores.............
//Our worker thread function
int worker(void* data);

//Data access semaphore
SDL_sem* gDataLock = NULL;

//The "data buffer"
int gData = -1;

int worker(void* data)
{
	printf("%s starting...\n", data);

	//Pre thread random seeding
	srand(SDL_GetTicks());

	//Work 5 times
	for (int i = 0; i < 50; ++i)
	{
		//Wait randomly
		SDL_Delay(16 + rand() % 32);

		//Lock
		SDL_SemWait(gDataLock);

		//Print pre work data
		printf("%s gets %d\n", data, gData);

		randNum = rand() % 2 + 1;

		if (randNum == 1)
		{
			//moved right!
			spriteRect->x += 10;

			spriteRect1->x += 10;

			spriteRect2->x += 10;

		}
		else
		{
			//moved left!
			spriteRect->x -= 10;
			spriteRect1->x -= 10;
			spriteRect2->x -= 10;
		}
			
			
		//"Work"
		//gData = rand() % 256;
		gData = gData + 1;

		//pos = gData;
		//spriteRect->x = pos;
		//Print post work data
		printf("%s sets %d\n\n", data, gData);

		//Unlock
		SDL_SemPost(gDataLock);

		//Wait randomly
		SDL_Delay(16 + rand() % 640);
	}

	printf("%s finished!\n\n", data);

	return 0;
}

/*int thread(void* ptr)
{
unsigned int result = 0;
Uint32 update, elapsed = 0;
update = 2000;

while (true)
{

if (SDL_mutexP(mut) == -1)
{
std::cout << "Process Artificial Intelligence Spinning 1" << std::endl;
}
else {
std::cout << "Mutex Locked1" << std::endl;
x += 1;
spriteRect->x = x;

std::cout << "Mutex Updating1" << std::endl;

if (SDL_mutexV(mut) == -1)
{
std::cout << "Unlock failed Spinning1" << std::endl;
}
std::cout << "Mutex UnLocked1" << std::endl;
SDL_Delay(1000);
}
}
return result;
}

int secondThread(void* ptr)
{
unsigned int result = 0;
Uint32 update, elapsed = 0;
update = 1000;

while (true)
{
if (SDL_mutexP(mut) == -1)
{
std::cout << "Process Artificial Intelligence Spinning 2" << std::endl;
}
else {
std::cout << "Mutex Locked 2" << std::endl;

x2 -= 1;
spriteRect1->x = x2;
std::cout << "Mutex Updating 2" << std::endl;

if (SDL_mutexV(mut) == -1)
{
std::cout << "Unlock failed Spinning2" << std::endl;
}
std::cout << "Mutex unLocked 2" << std::endl;
SDL_Delay(1000);
}
}
return result;
}
*/
int main(int, char**) {
	//Initialize semaphore
	gDataLock = SDL_CreateSemaphore(1);
	mut = SDL_CreateMutex();

	//initialise SDL system and the video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		QuitWithError("SDL_Init Error: ");

	}

	//Create a Window
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		QuitWithError("SDL_CreateWindow Error: ");

	}
	SDL_SetWindowFullscreen(win, SDL_WINDOWEVENT);

	bool quit = false;

	Mix_Music *music = NULL;
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1;
	std::string basepath(SDL_GetBasePath());
	music = Mix_LoadMUS((basepath + "background.wav").c_str());
	Mix_PlayMusic(music, -1);

	Render* renderer = new Render(win);

	//Main loop flag


	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);

	string bgPath = basepath + "background2.bmp";
	SDL_Surface* back = SDL_LoadBMP(bgPath.c_str());
	SDL_Rect* backGroundRect = renderer->AddSurfaceToRenderer(back, 0, -600, 1.0f);

	Level level = Level(World, renderer);
	Button button = Button(880, 39, World, renderer);
	Door door = Door(900, 0, renderer);
	Door threadDoor = Door(700, 0, renderer);
	Player player = Player(100, 500, World, renderer);
	int dir;
	//bool quit = false;
	vector<Cannon*> cannons;
	cannons.push_back(new Cannon(170, 358, World, renderer, 1));
	cannons.push_back(new Cannon(1010, 158, World, renderer, 2));
	MenuScene* menu = new MenuScene(1200, 100, renderer);

	std::string imagePath = basepath + "papu.bmp";

	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect = renderer->AddSurfaceToRenderer(sprite, x, y, 0.5f);

	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect1 = renderer->AddSurfaceToRenderer(sprite, x3, y3, 0.5f);

	sprite = SDL_LoadBMP(imagePath.c_str());
	spriteRect2 = renderer->AddSurfaceToRenderer(sprite, x2, y2, 0.5f);

	//SDL_Event e;
	/*
	//Mutex Threads being called
	SDL_Thread* id = SDL_CreateThread(thread, "MoveThread", (void*)NULL);
	SDL_Thread* id2 = SDL_CreateThread(secondThread, "MoveThread2", (void*)NULL);
	*/
	//game loop
	//Below, you will find all code relating to Semaphore. 
	//I will keep it within commented lines to keep things clear.


	//Event handler
	SDL_Event e;

	//Run the threads 
	srand(SDL_GetTicks());

	SDL_Thread* threadA = SDL_CreateThread(worker, "Thread A", (void*)"Thread A");
	SDL_Delay(16 + rand() % 32);
	SDL_Thread* threadB = SDL_CreateThread(worker, "Thread B", (void*)"Thread B");


	//........................................................................................


	while (!quit) {

		World.Step(1 / 60.f, 6, 2);
		while (SDL_PollEvent(&e) != 0) {
			if (inputHandler.CheckInput(SDLK_ESCAPE, e)) {
				quit = true;
			}
		}
		//SDL_Thread* id = SDL_CreateThread(thread,e, "MoveThread", (void*)NULL);
		if (menu->playBool == false && menu->quitBool == false) {
			renderer->DrawMenuScene();
			menu->Update(renderer);
		}

		if (menu->playBool == true)
		{
			//PLAY GAME STATE
			dir = player.Move(inputHandler, e);


			for (int i = 0; i < cannons.size(); i++)
			{
				cannons.at(i)->Update();
			}
			SDL_Rect rec(player.spriteRect);
			rec.y = player.GetY();

			for (int j = 0; j < cannons.size(); j++)
			{
				for (int i = 0; i < cannons.at(j)->fireballs.size(); i++)
				{
					if (cannons.at(j)->fireballs.at(i)->CheckCollision(&rec) == true)
					{
						std::cout << "Collision Detected!" << std::endl;
						player.Respawn();
						button.setOnce(false);
						button.buttonBody->SetTransform(b2Vec2(880 / SCALE, 39 / SCALE), 0);
						door.spriteRect->x = -1000;
						door.spriteRect->y = -1000;
						player.prevPosX.clear();
						player.prevPosY.clear();
						player.count = 0;
					}
				}
			}

			button.Update();

			if (button.CheckCollision(&rec) == true)
			{
				std::cout << "Collision Detected!" << std::endl;
				button.collision = true;
				button.spriteRect->x = -2000;
				button.spriteRect->y = -2000;
				button.buttonBody->SetTransform(b2Vec2(-2000, -2000), 0);
				//door.Draw(renderer);
			}
			if (door.CheckCollision(&rec) == true)
			{
				button.buttonBody->SetTransform(b2Vec2(880 / SCALE, 39 / SCALE), 0);
				std::cout << "Collision Detected!" << std::endl;
				player.Respawn();
				button.setOnce(false);
				door.spriteRect->x = -1000;
				door.spriteRect->y = -1000;
				player.prevPosX.clear();
				player.prevPosY.clear();
				player.count = 0;
				menu->playBool = false;
				menu->quitBool = false;
				menu->backGroundRect->x = 0;
				menu->current = 0;
				button.collision = false;
			}
			if (button.collision == false)
			{
				door.DrawCage(renderer);
			}
			if (button.collision == true)
			{
				door.DrawNoCage(renderer);
			}
			int ticks = SDL_GetTicks();
			int seconds = ticks / 50;
			int sprite = seconds % 8;
			renderer->Update(player.srcRect, player.dstRect, *player.LeftTexture, *player.RightTexture, *player.StandTexture, sprite, dir, player.moving, player.GetY());
			player.dstRect.w = player.spriteRect.w;
			player.dstRect.h = player.spriteRect.h;
			player.dstRect.x = player.spriteRect.x;
			player.dstRect.y = player.spriteRect.y + 5;
		}

		if (menu->quitBool == true)
		{
			quit = true;
		}
	}

	//Wait for threads to finish
	SDL_WaitThread(threadA, NULL);
	SDL_WaitThread(threadB, NULL);

	//SDL_DestroyRenderer(renderer->ren);
	//SDL_DestroyWindow(win);

	SDL_Quit();
	return 0;
}
