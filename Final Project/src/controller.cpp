#include "controller.h"
#include<iostream>

void Controller::HandleInput(bool &running, std::shared_ptr<Pacman> &pacman, std::shared_ptr<Map> &map) const{
	SDL_Event e;
	Direction direct;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          direct = up;
          break;

        case SDLK_DOWN:
          direct = down;
          break;

        case SDLK_LEFT:
					direct = left;
          break;

        case SDLK_RIGHT:
					direct = right;
          break;
      }

      pacman->status = direct;
			pacman->move(map, direct);
      

      map->Locate_character(0, pacman->Get_pose());
      map->Change_map(GridPhase::empty);
  
    }
  }  
};