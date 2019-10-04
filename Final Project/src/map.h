#ifndef MAP_H
#define MAP_H

#include<vector>
#include<mutex>
#include<thread>
#include<tuple>
#include <condition_variable>
#include <future>

#define GridSize 14

enum GridPhase
{  
	empty,
  occupied,
	food,
	laser,
	reverser,
};

class WaitingEat{
	public:
		void SetReverser();
		void SetPromise(std::promise<void> &&prms){ std::lock_guard<std::mutex> lock(_mutex); prmsEatReverser = std::move(prms);}

	private:
		std::mutex _mutex;
		std::promise<void> prmsEatReverser;
};

class Map{
	public:

		bool attack_flag = false;

		std::vector<std::vector<GridPhase>> Get_current_map() {return grid; }
		void Change_map(GridPhase status); 

		Map();
		void initialize();
		void Add_laser();
		void Add_reverser();
		void CheckReverser();
		
		void Locate_character(int index, std::tuple<int, int> pos_){ pos[index][0] = std::get<0>(pos_); pos[index][1]=std::get<1>(pos_);}
		bool check_pos();

		std::tuple<int, int> Get_pacman_pos(){return std::make_tuple(pos[0][0],pos[0][1]); }

	private:
		std::vector<std::vector<GridPhase>> grid;
		std::mutex _mutex;
		std::condition_variable cond_;
		WaitingEat _waitingEat;
		// int Grid_size = 14;

		std::vector<std::thread> threads;
		int pos[5][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
		int num_food;
		int num_reverser=0;
		
};

#endif