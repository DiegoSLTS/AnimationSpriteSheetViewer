#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(SpriteSheet *spriteSheet, int x, int y, int fps)
	: frameNumber(0), timeBetweenFrames(1000/fps), sheet(spriteSheet), lastChangeTime(0), x(x), y(y) {
	framesCount = sheet->frames.size();
}

SpriteAnimation::~SpriteAnimation() {}

void SpriteAnimation::Update(Uint32 deltaTime) {
	lastChangeTime += deltaTime;
	if (lastChangeTime >= timeBetweenFrames) {
		lastChangeTime -= timeBetweenFrames;
		frameNumber++;
		frameNumber %= framesCount;
	}
}

SDL_Rect* SpriteAnimation::GetCurrentFrame() {
	return &sheet->frames.at(frameNumber);
}

void SpriteAnimation::Draw(SDL_Renderer* renderer) {
	SDL_Rect* frame = GetCurrentFrame();

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = frame->w;
	dst.h = frame->h;

	SDL_RenderCopy(renderer, sheet->tex, frame, &dst);
}