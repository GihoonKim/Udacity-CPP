#ifndef MAP_H
#define MAP_H

#include<vector>
#include<mutex>
#include<thread>

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

	private:
		std::vector<std::vector<GridPhase>> grid;
		std::mutex _mutex;
		// int Grid_size = 14;

		std::vector<std::thread> threads;
		
		
};

#endif