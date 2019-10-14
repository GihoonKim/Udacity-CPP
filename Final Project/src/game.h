#ifndef GAME_H
#define GAME_H

#include <random>
#include <condition_variable>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "pacman.h"
#include "enemy.h"
#include "map.h"

class Game {
  public:

  	bool running;
    Game(std::size_t grid_width, std::size_t grid_height);

	~Game();
    void Run(Controller const &controller, Renderer &renderer,
						std::size_t target_frame_duration);

	void end_game(Controller const &controller, Renderer &renderer, 
						std::size_t target_frame_duration);

	int GetScore() const;
	void Init(int init_x, int init_y);
	Uint16 num_enemy=4;

	void send();
	int receive();

	void Check_game();

	
    
	private:
		std::condition_variable cond_;
		std::mutex _mutex;
		std::vector<std::thread> threads;

		std::shared_ptr<Pacman> pacman;
		std::vector<std::shared_ptr<Enemy>> enemy_group;
		std::shared_ptr<Map> map;

		std::random_device dev;
		std::mt19937 engine;

		int end_status;

		int score{0};

		void Update();
		

};

#endif
