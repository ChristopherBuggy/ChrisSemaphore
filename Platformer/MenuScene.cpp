#include "MenuScene.h"
static const float SCALE = 30.f;
bool quit; 
bool play;
MenuScene::MenuScene(int x, int y, Render* renderer)
{
	std::string basepath(SDL_GetBasePath());

	playPath1 = basepath + "StartGame2.bmp";
	quitPath1 = basepath + "Quit2.bmp";

	playPath2 = basepath + "StartGame1.bmp";
	quitPath2 = basepath + "Quit1.bmp";

	quitBool = false;
	playBool = false;
	//Background stuff

	bgPath = basepath + "background.bmp";
	back = SDL_LoadBMP(bgPath.c_str());
	backGroundRect = renderer->AddSurfaceToRenderer(back, 0, 0, 1.0f);

	//First set of images.
	play1 = SDL_LoadBMP(playPath1.c_str());
	playRect1 = renderer->AddSurfaceToRenderer(play1, 300, 300, 1.0f);

	//Second set of images.
	play2 = SDL_LoadBMP(playPath2.c_str());
	playRect2 = renderer->AddSurfaceToRenderer(play2, 300, 300, 1.0f);

	quit2= SDL_LoadBMP(quitPath2.c_str());
	quitRect2 = renderer->AddSurfaceToRenderer(quit2, 700, 300, 1.0f);

	quit1 = SDL_LoadBMP(quitPath1.c_str());
	quitRect1 = renderer->AddSurfaceToRenderer(quit1, 700, 300, 1.0f);
	
	
	current = 1;
}

void MenuScene::Update(Render* renderer)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_A]) {
		playRect1->x = 100000000;
		quitRect1->x = 700;

		playRect2-> x = 300;
		quitRect2-> x = 1000000;
		std::string basepath(SDL_GetBasePath());

		current = 1;
	}

	if (keys[SDL_SCANCODE_D]) {
		playRect1->x = 300;
		quitRect1->x = 100000;

	

		quitRect2->x = 700;
		playRect2->x = 100000;

		current = 2;
	}

	if (keys[SDL_SCANCODE_RETURN]) {
		if (current == 1) {
			
			quitRect1->x = 100000000;
			playRect1->x = 100000000;

			playRect2->x = 100000000;
			quitRect2->x = 100000000;

			//Move the background
			backGroundRect->x = 100000;

			//quitRect->w = 10;
			playBool = true;
			quitBool = false;
			
		}

		if (current == 2) {

			playBool = false;
			quitBool = true;
		
			playRect1->x = 100000000;
			quitRect1->x = 100000000;
		}


	}
}
