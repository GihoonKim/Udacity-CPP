#include "renderer.h"
#include "game.h"
#include "controller.h"

#include<iostream>

int main() {
	constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

    Renderer renderer(700,700,10,10);
    Controller controller;
    // Map map;

    Game game(10,10);

    // std::cout<<"test"<<std::endl;
    std::thread t(&Game::Check_game,&game);

    game.Run(controller, renderer, kMsPerFrame);

    game.end_game(controller,renderer,kMsPerFrame);

    // if game.end status = 0 -> plot loss, else -> plot win
    // check any key input
    // game restart or end

    t.join();

    return 0;
}