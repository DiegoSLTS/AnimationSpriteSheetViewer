#pragma once

#include "SpriteSheet.h"

class SpriteAnimation {
public:
	SpriteAnimation(SpriteSheet *sheet, int x, int y, int fps);
	virtual ~SpriteAnimation();

	void Update(Uint32 milliseconds);
	void Draw(SDL_Renderer* renderer);

private:
	SpriteSheet* sheet;
	int frameNumber;
	int framesCount;
	Uint32 timeBetweenFrames; //in milliseconds
	Uint32 lastChangeTime;

	int x;
	int y;

	SDL_Rect* GetCurrentFrame();
};

