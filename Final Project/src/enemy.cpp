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

	constexpr std::size_t kFramesPerSecond{10};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;

	bool running = true;

	while (running){

		frame_start = SDL_GetTicks();

		//Input, Update, Render - the main game loop.

		pacman_pos = map_->Get_pacman_pos();
		
		Heuristic_move(pacman_pos, map_);

		// map_->Locate_character(this->index_,this->Get_pose());

		frame_end = SDL_GetTicks();


		frame_duration = frame_end - frame_start;
		if (frame_duration < kMsPerFrame) {
				SDL_Delay(kMsPerFrame - frame_duration);
				}

	}

}


void Enemy::Heuristic_move(std::tuple<int,int> pos, std::shared_ptr<Map> &map){
	
	std::vector<Direction> prior_direct;

	Direction direct;
	int target_x = std::get<0> (pos);
	int target_y = std::get<1> (pos);

	int temp_x = Enemy::pos_x;
	int temp_y = Enemy::pos_y;

	auto diff_x = target_x - temp_x;
	auto diff_y = target_y - temp_y;

	if(abs(diff_x)>abs(diff_y)){
		if(diff_x>0){
			direct = down;
		}
		else{
			direct = up;
		}
	}
	else{
		if(diff_y>0){
			direct = right;
		}
		else{
			direct = left;
		}
	}
	
	Enemy::move(map,direct);

	if(temp_x==std::get<0>(Enemy::Get_pose()) | temp_y ==std::get<1>(Enemy::Get_pose())){
		
		Enemy::move(map,get_rand()); //need to be changed
	}
}

Direction Enemy::get_rand(){
	int idx = rand()%4;
	switch(idx){
		case 0:
			return Direction::up;
			break;
		case 1:
			return Direction::down;
			break;
		case 2:
			return Direction::left;
			break;
		case 3:
			return Direction::right;
			break;
			
	}
}
