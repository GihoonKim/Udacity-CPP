#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "SDL2/SDL.h"
#include "character.h"
// #include "t_line.h"


class Pacman : public Character{
	public:

		Pacman();
	// Tetris(int grid_width, int grid_height)
	// 			: 

		void Update();

		float speed{0.1f};

		Direction status {Direction::right};

	private:
		// std::vector<Line> line_storage; 

};

#endif