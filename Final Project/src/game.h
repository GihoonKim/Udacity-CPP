#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "pacman.h"
#include "enemy.h"
#include "map.h"

class Game {
  public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const &controller, Renderer &renderer,
						std::size_t target_frame_duration);

	int GetScore() const;
	void Init(int init_x, int init_y);

    
	private:
		
		std::shared_ptr<Pacman> pacman;
		std::vector<std::shared_ptr<Enemy>> enemy_group;
		std::shared_ptr<Map> map;

		std::random_device dev;
		std::mt19937 engine;

		int score{0};

		void Update();
		

};

#endif
