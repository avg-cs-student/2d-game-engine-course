#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Game {
private:
	bool running = false;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};
