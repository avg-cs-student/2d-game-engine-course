#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

static constexpr int FPS = 30;
static constexpr int MILLISECONDS_PER_FRAME = 1'000 / FPS;

class Game {
private:
	bool running = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int previousFrameMs;

public:
	Game();
	~Game();
	void Setup();
	void Initialize();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	size_t windowWidth;
	size_t windowHeight;
};
