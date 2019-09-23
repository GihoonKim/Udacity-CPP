#include "game.h"
#include <iostream>
#include "SDL2/SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
	: engine(dev())
	{
		int x = 8; int y=1; // unnecessary
		Game::Init(x,y);
	}


void Game::Init(int x, int y){

	//Generate map
	map = std::make_shared<Map>();

	//define number of enemy and their initial position
	Uint16 num_enemy=4;
	int Enemy_pos[2][4] {{30,30,35,35},{30,35,30,35}};
	int Ego_pos[2] {40,5};

	//Generate enemy
	for(int n=0; n<num_enemy;n++){
		enemy_group.push_back(std::make_shared<Enemy>(map, n));
		enemy_group.at(n)->Set_pose(Enemy_pos[0][n], Enemy_pos[1][n]);
	}

	//Generate pacman
	pacman = std::make_shared<Pacman>();
	pacman->Set_pose(Ego_pos[0],Ego_pos[1]);
	

	
}


void Game::Run(Controller const &controller, Renderer &renderer, 
					std::size_t target_frame_duration){

	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;

	bool running = true;

	while (running){

		// SDL_Event e;
		// while (SDL_PollEvent(&e))
		// {
		// 		if (e.type == SDL_QUIT)
		// 				running = false; break;
		// }

		frame_start = SDL_GetTicks();

		//Input, Update, Render - the main game loop.

		controller.HandleInput(running, pacman, map);
		Update();
		renderer.Render(map->Get_current_map(), pacman, enemy_group);

		frame_end = SDL_GetTicks();
		
		
		frame_duration = frame_end - frame_start;
		if (frame_duration < target_frame_duration) {
				SDL_Delay(target_frame_duration - frame_duration);
				}

	}
}

void Game::Update(){
	
}



