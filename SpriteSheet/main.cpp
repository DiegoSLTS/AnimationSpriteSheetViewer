#include <iostream>
#include <fstream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "SpriteSheet.h"
#include "SpriteAnimation.h"

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[]) {

	SDL_SetMainReady();

	// default values
	std::string fileName = "example.png";
	int frameWidth = 128;
	int frameHeight = 128;
	int framesCount = -1;
	int fps = 25;

	// arguments parsing
	for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]).compare("-p") == 0) { // path to the spritesheet file, relative to the application path
            if (i + 1 < argc)
                fileName = std::string(argv[++i]);
            else {
				std::cerr << "argument missing after -p" << std::endl;
                return 1;
            }
        } else if (std::string(argv[i]).compare("-s") == 0) { // size (i.e. dimensions, resolution) of each frame inside the spritesheet
            if (i + 1 < argc) {
				int values = sscanf_s(argv[++i], "%dx%d", &frameWidth, &frameHeight);
				if (values != 2) {
					std::cerr << "argument after -s not valid, using default (" << frameWidth << "x" << frameHeight << ")" << std::endl;
				}
			} else {
				std::cerr << "argument missing after -s" << std::endl;
                return 1;
            }
        } else if (std::string(argv[i]).compare("-t") == 0) { // frames count
            if (i + 1 < argc) {
				int values = sscanf_s(argv[++i], "%d", &framesCount);
				if (values != 1) {
					std::cerr << "argument after -t not valid, using default (rows * columns)" << std::endl;
				}
			} else {
				std::cerr << "argument missing after -t" << std::endl;
                return 1;
            }
        } else if (std::string(argv[i]).compare("-f") == 0) { // frames per second (i.e. speed of the animation)
            if (i + 1 < argc) {
                int values = sscanf_s(argv[++i], "%d", &fps);
				if (values != 1) {
					std::cerr << "argument after -f not valid, using default (" << fps << ")" << std::endl;
				}
			} else {
				std::cerr << "argument missing after -f" << std::endl;
                return 1;
            }
        }
    }

	std::string spriteSheetPath = SDL_GetBasePath();
	spriteSheetPath.append(fileName);
	std::ifstream infile(spriteSheetPath.c_str());
    if (!infile.good()) {
		std::cout << "file not found: " << spriteSheetPath.c_str() << std::endl;
		return 2;
	}

	// SDL initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 3;
	}

	SDL_Window *window = SDL_CreateWindow("SpriteSheet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_Quit();
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		return 4;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		std::cout << "CreateRenderer error: " << SDL_GetError() << std::endl;
		return 5;
	}
	SDL_RenderClear(renderer);

	// loading spritesheet
	SpriteSheet sheet(renderer,spriteSheetPath.c_str(),frameWidth,frameHeight,framesCount);

	std::vector<SpriteAnimation> animations;
	Uint32 previousTime = SDL_GetTicks();

	// main loop
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		// input control
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;

			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;

			if (e.type == SDL_MOUSEBUTTONDOWN)
				animations.emplace_back(&sheet,e.button.x,e.button.y,fps);
		}

		// screen update
		Uint32 currentTime = SDL_GetTicks();
		Uint32 deltaTime = currentTime - previousTime;
		for (auto&& animation : animations)
			animation.Update(deltaTime);
		previousTime = currentTime;

		// scene render
		SDL_RenderClear(renderer);
		for (auto&& animation : animations)
			animation.Draw(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}