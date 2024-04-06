#include <iostream>
#include <memory>

#include "logger/ConsoleLogger.h"
#include "game/Game.h"

int main(int argc, char* argv[]) {
    auto logger = std::make_unique<ConsoleLogger>();
    Game game(std::move(logger));

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
