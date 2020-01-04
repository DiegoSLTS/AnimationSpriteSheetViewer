#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class SpriteSheet {
public:
	SpriteSheet(SDL_Renderer* renderer, const char* fileName, int frameWidth, int frameHeight, int framesCount);
	virtual ~SpriteSheet();

	SDL_Texture* tex;
	std::vector<SDL_Rect> frames;
};

