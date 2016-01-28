#ifndef Render_H
#define Render_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class Render {
private:
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> dstRects;
public:
	SDL_Renderer *ren;
	SDL_Rect source;
	Render(SDL_Window *win) {
		dstRects.reserve(100);
		//creating a renderer that is linked to the render class 
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr) {
			SDL_DestroyWindow(win);
			QuitWithError("SDL_CreateRenderer Error: ");
		}
		//set background color
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	}

	//updating the renderer and drawing what is within it
	void Update(SDL_Rect src, SDL_Rect dst, SDL_Texture &leftTexture, SDL_Texture &rightTexture, SDL_Texture &stillTexture, int sprite, int dir, bool moving, int y)
	{
		//clear the screen
		SDL_RenderClear(ren);

		//copy the textures to the renderer and give them a destination
		int numberTextures = textures.size();
		for (int i = 0; i < numberTextures; i++) {
			SDL_Rect rec;
			rec.x = dstRects.at(i).x;
			rec.y = dstRects.at(i).y - y + 500;
			rec.w = dstRects.at(i).w;
			rec.h = dstRects.at(i).h;
			SDL_RenderCopy(ren, textures[i], NULL, &rec);
		}

//<<<<<<< HEAD
		if (&leftTexture != NULL && &rightTexture != NULL && &stillTexture != NULL)
		{			
			if (dir == 1 && dir != 2)
			{
				source = { sprite * 20, 0, 20, 40 };
				SDL_RenderCopy(ren, &leftTexture, &source, &dst);
			}

			if (dir == 2 && dir != 1)
			{
				source = { sprite * 20, 0, 20, 40 };
				SDL_RenderCopy(ren, &rightTexture, &source, &dst);
			}
			
		}

		if (moving == false)
		{
			source = {sprite * 20, 0, 20, 40 };
			SDL_RenderCopy(ren, &stillTexture, &source, &dst);
		}


//=======
//>>>>>>> RewindTimePlayer
		//update the screen with rendering operations
		SDL_RenderPresent(ren);
	}


	void DrawMenuScene()
	{
		//clear the screen
		SDL_RenderClear(ren);

		//copy the textures to the renderer and give them a destination
		int numberTextures = textures.size();
		for (int i = 0; i < numberTextures; i++) {
			SDL_RenderCopy(ren, textures[i], NULL, &dstRects[i]);
		}

		//update the screen with rendering operations
		SDL_RenderPresent(ren);


	}

	void RemoveSurface(SDL_Surface surface)
	{

	}
	

	//adding texture to the renderer with the position
	SDL_Rect* AddSurfaceToRenderer(SDL_Surface *bmp, float x, float y, float scale) {
		//getting the width / height from the texture
		SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		if (texture == nullptr) {
			QuitWithError("SDL_CreateTextureFromSurface Error: ");
		}
		int iW, iH;
		SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);

		SDL_Rect dstRect;
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = iW * scale;
		dstRect.h = iH * scale;

		int rectPos = dstRects.size();
		dstRects.push_back(dstRect);
		textures.push_back(texture);

		return &dstRects[rectPos];
	}

	//rendering texture
	SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
	{
		//Open the font
		TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
		if (font == nullptr) {
			logSDLError("TTF_OpenFont");
			return nullptr;
		}
		//We need to first render to a surface as that's what TTF_RenderText
		//returns, then load that surface into a texture
		SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
		if (surf == nullptr) {
			TTF_CloseFont(font);
			logSDLError("TTF_RenderText");
			return nullptr;
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (texture == nullptr) {
			logSDLError("CreateTexture");
		}
		//Clean up the surface and font
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;
	}

	void logSDLError(const std::string &msg) {
		//std::cout << msg << " error: " << SDL_GetError() << std::endl;

	}

	int QuitWithError(const std::string &msg) {
		//std::cout << msg << " error: " << SDL_GetError() << std::endl;
		SDL_Delay(1000); //give user a chance to read error
		SDL_Quit();
		return 1;
	}

};
#endif