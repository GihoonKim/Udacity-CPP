#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "SDL2/SDL.h"
#include "character.h"
// #include "t_line.h"


class Pacman : public Character{
	public:
		enum class Direction {kUpm, kDown, kLeft, kRight};

		Pacman();
	// Tetris(int grid_width, int grid_height)
	// 			: 

		void Update();

		float speed{0.1f};

	private:
		// std::vector<Line> line_storage; 

};

#endif