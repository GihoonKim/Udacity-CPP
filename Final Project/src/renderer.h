#ifndef RENDERER_H
#define RENDERER_H

#define MapSize 50

#include <vector>
#include "SDL2/SDL.h"
#include "map.h"
#include "pacman.h"
#include "enemy.h"

class Renderer {
	public:
		Renderer(const std::size_t screen_width, const std::size_t screen_height,
							const std::size_t grid_width, const std::size_t grid_height);
		
		~Renderer();
		// void Render(Tetris const tetris);
		void Render(std::vector<std::vector<GridPhase>> const &current_map, std::shared_ptr<Pacman> &pacman, std::vector<std::shared_ptr<Enemy>> &enemy_group);
		void UpdateWindowTitle(int score, int fps);

	private:
		SDL_Window *sdl_window;
		SDL_Renderer *sdl_renderer;

		SDL_Surface * img;
		SDL_Texture * texture;


		std::vector<std::vector<GridPhase>> current_map;

		const std::size_t screen_width;
		const std::size_t screen_height;
		const std::size_t grid_width;
		const std::size_t grid_height;
};

#endif