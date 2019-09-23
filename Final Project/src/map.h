#ifndef MAP_H
#define MAP_H

#include<vector>
#include<mutex>
#include<thread>
#include<tuple>

#define GridSize 14

enum GridPhase
{  
	empty,
  occupied,
	food,
	laser,
};

class Map{
	public:

		std::vector<std::vector<GridPhase>> Get_current_map() {return grid; }
		void Change_map(int x, int y, GridPhase status) { grid[x][y]=status; }

		Map();
		void initialize();
		void Add_laser();
		
		void Locate_character(int index, std::tuple<int, int> pos_){ pos[index][0] = std::get<0>(pos_); pos[index][1]=std::get<1>(pos_);}
		bool check_pos();

	private:
		std::vector<std::vector<GridPhase>> grid;
		std::mutex _mutex;
		// int Grid_size = 14;

		std::vector<std::thread> threads;
		int pos[5][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
		
};

#endif