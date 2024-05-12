#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../logger/Logger.h"
#include "../ECS/ECS.h"

static constexpr int FPS = 600;
static constexpr int MILLISECONDS_PER_FRAME = 1000.0 / FPS;

class Game {
private:
	std::unique_ptr<Logger> logger;
	bool running = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int previousFrameMs = 0;

public:
	Game(std::unique_ptr<Logger> logger);
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
