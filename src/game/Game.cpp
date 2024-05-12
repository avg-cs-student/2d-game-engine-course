#include "Game.h"

Game::Game(std::unique_ptr<Logger> logger_) : logger(std::move(logger_)) {
	logger->Log("Game constructor called!");

	running = true;
}

Game::~Game() {
	logger->Log("Game destructor called!");
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

void Game::Setup() {
	// Todo:
	// Entity tank = registry.CreateEntity();
	// tank.AddComponent<TransformComponent>();
	// tank.AddComponent<BoxColliderComponent();
	// tank.AddComponent<SpriteComponent>("./assets/images/tank.png")
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

	// Todo:
	// MovementSystem.Update();
	// CollisionSystem.Update();
	// DamageSystem.Update();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
