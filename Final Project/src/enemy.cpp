#include"enemy.h"
#include<iostream>
#include<thread>

Enemy::Enemy(std::shared_ptr<Map> &map, int index) : map_(map), index_(index){
	std::cout<<"create Enemy"<<std::endl;

	threads.emplace_back(&Enemy::Control,this);
	//using thread perform own task.

}

void Enemy::Control(){

	Direction direct;

	constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

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

		int temp = rand()%4;

		switch(temp){
			case 0:
				direct = up;
				break;
			case 1:
				direct = down;
				break;
			case 2:
				direct = left;
				break;
			case 3:
				direct = right;
				break;
		}


		frame_start = SDL_GetTicks();

		//Input, Update, Render - the main game loop.

		Enemy::move(this->map_, direct);

		map_->Locate_character(this->index_,this->Get_pose());

		frame_end = SDL_GetTicks();


		frame_duration = frame_end - frame_start;
		if (frame_duration < kMsPerFrame) {
				SDL_Delay(kMsPerFrame - frame_duration);
				}

	}

}
// Direction Enemy::Heuristic_search(){
// 	auto[map_x, map_y] = Enemy::CurrentMap_pose(Enemy::pos_x, Enemy::pos_y);


// }
