#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pacman.h"

class Controller {
	public:
		void HandleInput(bool &running, std::shared_ptr<Pacman> &pacman, std::shared_ptr<Map> &map) const;

	private:
		void ChangeDirection(Pacman &pacman, Pacman::Direction input) const;

};

#endif