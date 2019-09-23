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

    std::cout<<"test"<<std::endl;
    game.Run(controller, renderer, kMsPerFrame);

    return 0;
}