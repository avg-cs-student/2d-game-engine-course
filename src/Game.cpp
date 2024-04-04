#include "Game.h"

Game::Game() {
	std::cout << "Game constructor called!" << std::endl;
	running = true;
}

Game::~Game() {
	std::cout << "Game destructor called!" << std::endl;
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL" << std::endl;
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 1920; //displayMode.w;
	windowHeight = 1080; //displayMode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	running = true;
}

void Game::Run() {
	Setup();
	while (running) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				break;
		}
	}
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(100.0, 50.0);
}

void Game::Update() {
	int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - previousFrameMs);
	if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}

	// Difference in ticks since the last frame, converted to seconds
	double deltaTime_s = (SDL_GetTicks() - previousFrameMs) / 1'000.0;

	// If we are too fast, waste time until we reach target FPS
	previousFrameMs = SDL_GetTicks();

	playerPosition.x += playerVelocity.x * deltaTime_s;
	playerPosition.y += playerVelocity.y * deltaTime_s;
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Draw a PNG texture
	SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Destination rectangle that we want to place our texture
	SDL_Rect dstRect = { 
		static_cast<int>(playerPosition.x),
		static_cast<int>(playerPosition.y),
		32,
		32
	};
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
