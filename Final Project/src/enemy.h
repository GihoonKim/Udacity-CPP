#ifndef ENEMY_H
#define ENEMY_H

#include "SDL2/SDL.h"
#include "character.h"

class Enemy : public Character {
  public:
  
    Enemy(std::shared_ptr<Map> &map, int index);

		void Control();

		void Heuristic_move(std::tuple<int,int> pos, std::shared_ptr<Map> &map);
		Direction get_rand();
		

	private:
		

		std::shared_ptr<Map> map_;
		int index_;
		std::tuple<int,int> pacman_pos;
};

#endif
