#include "game.h"
#include <iostream>
#include "SDL2/SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
	: engine(dev())
	{
		int x = 8; int y=1; // unnecessary
		Game::Init(x,y);
	}
	
Game::~Game()
{
	for (size_t i=0; i<threads.size() ; i++){ threads[i].detach(); }

    // std::cout<<"game destruct"<<std::endl;
}

void Game::Init(int x, int y){

	//Generate map
	map = std::make_shared<Map>();

	//define number of enemy and their initial position
	
	int Enemy_pos[2][4] {{30,30,35,35},{30,35,30,35}};
	int Ego_pos[2] {40,5};

	//Generate enemy
	for(int n=0; n<num_enemy;n++){
		enemy_group.push_back(std::make_shared<Enemy>(map, n+1));
		enemy_group.at(n)->Set_pose(Enemy_pos[0][n], Enemy_pos[1][n]);
	}

	//Generate pacman
	pacman = std::make_shared<Pacman>();
	pacman->Set_pose(Ego_pos[0],Ego_pos[1]);

	// threads.emplace_back(&Game::Check_game, this);
	
}


void Game::Run(Controller const &controller, Renderer &renderer, 
					std::size_t target_frame_duration){

	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;


	running = true;

	while (running){

		frame_start = SDL_GetTicks();

		//Input, Update, Render - the main game loop.

		controller.HandleInput(running, pacman, map);
		Update();
		renderer.Render(map, pacman, enemy_group);
		renderer.UpdateWindowTitle(score);
		frame_end = SDL_GetTicks();
		
		
		frame_duration = frame_end - frame_start;
		if (frame_duration < target_frame_duration) {
				SDL_Delay(target_frame_duration - frame_duration);
				}

	}

	

	
	
	
	//gdb -> run
}

void Game::Update(){

	map->Locate_character(0, pacman->Get_pose());
    map->Change_map(GridPhase::empty);

	for (int i=0; i<4; i++){
		if(enemy_group.at(i)->alive){
			map->Locate_character(i+1,enemy_group.at(i)->Get_pose());

			if(map->comp_pos(i+1)){
				if (map->attack_flag) { enemy_group.at(i)->alive=false; num_enemy -=1; send(); }
				else{pacman->alive=false; send(); }
			}
		}
	}

	if(map->num_food==0) {send(); }

	Game::score = (88-map->num_food)*10 + (4-num_enemy)*100;

}

void Game::end_game(Controller const &controller, Renderer &renderer, 
					std::size_t target_frame_duration){

	Uint32 start_time = SDL_GetTicks();
	Uint32 current_time;
	// std::cout<<"change state"<<std::endl;
	SDL_Event e;

		
	while(true){

		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
			} 
		}
		// controller.HandleInput(running, pacman, map);
		renderer.Render_end(end_status);
		SDL_Delay(target_frame_duration);

		current_time = SDL_GetTicks();
		
		
		if(current_time-start_time>5000){break; }

	}
		


}
void Game::Check_game(){
	while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//mutex lock
		end_status = Game::receive();

		break;
	}
}

void Game::send(){
	// 
	std::lock_guard<std::mutex> uLock(_mutex);
	cond_.notify_one();
}

int Game::receive(){
	std::unique_lock<std::mutex> uLock(_mutex);

	cond_.wait(uLock, [this] {return (num_enemy==0 | pacman->alive==false | map->num_food==0);});

	running = false;

	if(pacman->alive == false){ return std::move(0);}
	else {return std::move(1);}

}



