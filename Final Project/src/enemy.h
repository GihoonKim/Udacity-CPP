#ifndef ENEMY_H
#define ENEMY_H

#include "SDL2/SDL.h"
#include "character.h"

class Enemy : public Character {
  public:
  
    Enemy(std::shared_ptr<Map> &map, int index);

		void Control();

	private:

		std::shared_ptr<Map> map_;
		int index_;
};

#endif
