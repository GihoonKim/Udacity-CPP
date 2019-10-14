#ifndef CHARACTER_H
#define CHARACTER_H

#include <tuple>
#include "map.h"


enum Direction{
	up,
	down,
	left,
	right,
};

class Character{
  public:

		~Character();
		
		bool alive = true;
		std::string name;
		
		std::tuple<int,int> CurrentMap_pose(); //pos_x/5 posy/5
		std::tuple<int,int> Get_pose(){return std::make_tuple(pos_x, pos_y);};
		void Set_pose(int &pos_X, int &pos_Y){pos_x = pos_X; pos_y = pos_Y;};

		void move(std::shared_ptr<Map> &map, Direction direct);

	protected:
		int pos_x, pos_y;
		std::vector<std::thread> threads;

	private:

		bool Valid_direction_check(std::shared_ptr<Map> &map, int &pos_x, int &pos_y, Direction direct);

};

#endif