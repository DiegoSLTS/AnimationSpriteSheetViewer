#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const char* fileName, int frameWidth, int frameHeight, int framesCount) {
	tex = IMG_LoadTexture(renderer, fileName);

	if (tex == nullptr) {
		std::cout << "IMG_LoadTexture error: " << SDL_GetError() << std::endl;
		throw 5;
	}

	int texWidth, texHeight;
	SDL_QueryTexture(tex, NULL, NULL, &texWidth, &texHeight);

	int framesPerRow = texWidth / frameWidth;
	int framesPerColumn = texHeight / frameHeight;
	int tempFramesCount = framesPerRow * framesPerColumn;
	if (framesCount > 0 && framesCount < tempFramesCount)
		tempFramesCount = framesCount;

	for (int i = 0; i < tempFramesCount; ++i) {
		SDL_Rect frame;
		frame.x = i / framesPerRow * frameWidth;
		frame.y = i % framesPerColumn * frameHeight;
		frame.w = frameWidth;
		frame.h = frameHeight;
		frames.push_back(frame);
	}
}


SpriteSheet::~SpriteSheet() {
	SDL_DestroyTexture(tex);
}
