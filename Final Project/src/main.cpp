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
    // std::size_t target_frame_duration = kMsPerFrame;
    // Uint32 frame_end;
    // Uint32 frame_start;
    // Uint32 frame_duration;
    // std::vector<std::vector<GridPhase>> grid;
    // bool program_running = true;

    // while(program_running){

    //     SDL_Event e;
    //     while (SDL_PollEvent(&e))
    //     {
    //         if (e.type == SDL_QUIT)
    //             program_running = false; break;
    //     }

    //     frame_start = SDL_GetTicks();
        
    //     grid = map.Get_current_map();

    //     rend.Render(grid);

    //     frame_end = SDL_GetTicks();
    //     frame_duration = frame_end - frame_start;

    //     if (frame_duration < target_frame_duration) {
    //         SDL_Delay(target_frame_duration - frame_duration);
    //         }

        

    // }
	
}