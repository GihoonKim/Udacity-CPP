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

		pacman_pos = map_->Get_pacman_pos();
		
		Heuristic_move(pacman_pos, map_);

		Enemy::move(this->map_, direct);

		map_->Locate_character(this->index_,this->Get_pose());

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

	// if(diff_y < 0){
	// 	prior_direct.push_back(left);
	// 	if(diff_x < 0){
	// 		prior_direct.push_back(up);
	// 		prior_direct.push_back(down);
	// 	}
	// 	else if(diff_x >=0){
	// 		prior_direct.push_back(down);
	// 		prior_direct.push_back(up);
	// 	}
	// 	prior_direct.push_back(right);
	// }
	// else if(diff_y>=0){
	// 	prior_direct.push_back(right);
	// 	if(diff_x < 0){
	// 		prior_direct.push_back(up);
	// 		prior_direct.push_back(down);
	// 	}
	// 	else if(diff_x >=0){
	// 		prior_direct.push_back(down);
	// 		prior_direct.push_back(up);
	// 	}
	// 	prior_direct.push_back(left);
	// }

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
	if(temp_x==std::get<0>(Enemy::Get_pose()) | temp_y ==std::get<1>(Enemy::Get_pose())){}
	else{
		Enemy::move(map,get_rand());
	}

	std::cout<<"pac_pos : (" <<target_x<<","<<target_y<<"), enemy_pos : ("<<temp_x<<","<<temp_y<<")"<<" "<<direct<<std::endl;
	// for (size_t i=0; i<4 ; i++){
	// 	Enemy::move(map,prior_direct[i]);

	// 	if(temp_x==std::get<0>(Enemy::Get_pose()) | temp_y ==std::get<1>(Enemy::Get_pose())){}
	// 	else{
	// 		break;
	// 	}

	// }


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
