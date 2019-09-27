#include "renderer.h"
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "pacman.h"
#include "enemy.h"

Renderer::Renderer(const std::size_t screen_width,
									 const std::size_t screen_height,
									 const std::size_t grid_width, const std::size_t grid_height)
		: screen_width(screen_width),
			screen_height(screen_height),
			grid_width(grid_width),
			grid_height(grid_height) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize. \n";
		std::cerr << "SDL_Error: " <<SDL_GetError() << "\n";
	}

	// create window
	sdl_window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED, 
																SDL_WINDOWPOS_CENTERED, screen_width,
																screen_height, SDL_WINDOW_SHOWN);

	if (nullptr == sdl_window) {
		std::cerr << "Window could not be created.\n";
		std::cerr << "SDL_Error : " << SDL_GetError() << "\n";
	}


	// create renderer
	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == sdl_renderer) {
		std::cerr << "Renderer could not be created.\n";
		std::cerr << "SDL_Error : " << SDL_GetError() << "\n";
	}

	// Download image need
	

	
	// SDL_Surface * img_pac_b = SDL_LoadBMP("./Image/pac_b");
	// SDL_Surface * img_pac_c = SDL_LoadBMP("./Image/pac_c");

	// SDL_Surface * img_enemy_a = SDL_LoadBMP("./Image/enemy_a");
	// SDL_Surface * img_enemy_b = SDL_LoadBMP("./Image/enemy_b");
	// SDL_Surface * img_enemy_c = SDL_LoadBMP("./Image/enemy_c");
	
}

Renderer::~Renderer() {
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Renderer::Render(std::vector<std::vector<GridPhase>> const &current_map, std::shared_ptr<Pacman> &pacman, std::vector<std::shared_ptr<Enemy>> &enemy_group) {

	
	// SLD_Rect block;
	// block.w = screen_width / grid_width;
	// block.h = screen_height / grid_height;
	
	// SDL_DestroyTexture(texture);
	// SDL_FreeSurface(img_pac_a);

	// Clear screen
	SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(sdl_renderer);

	

	SDL_Rect block;
	

	for (size_t i=0; i<current_map.size();i++){
		for (size_t j=0 ; j<current_map[0].size() ; j++){
			if (current_map[i][j]== GridPhase::occupied){
				SDL_SetRenderDrawColor(sdl_renderer, 90, 97, 204, 100);
				block.w = 40;
				block.h = 40;
				block.y = i*MapSize+5;
				block.x = j*MapSize+5;
				SDL_RenderFillRect(sdl_renderer, &block);
			}
			else if(current_map[i][j]== GridPhase::laser){
				
				SDL_SetRenderDrawColor(sdl_renderer, 220, 0, 0, 100);
				block.w = 50;
				block.h = 10;
				block.y = i*MapSize+20;
				block.x = j*MapSize;
				SDL_RenderFillRect(sdl_renderer, &block);
			}
			else if(current_map[i][j]==GridPhase::food){

				SDL_SetRenderDrawColor(sdl_renderer,235,229,52,100);
				block.w = 10;
				block.h = 10;
				block.y = i*MapSize+20;
				block.x = j*MapSize+20;
				SDL_RenderFillRect(sdl_renderer, &block);
			}
			else if(current_map[i][j]==GridPhase::reverser){

				SDL_SetRenderDrawColor(sdl_renderer,255,143,242,50);
				block.w = 20;
				block.h = 20;
				block.y = i*MapSize+15;
				block.x = j*MapSize+15;
				SDL_RenderFillRect(sdl_renderer, &block);
			}
		}
	}

	// SDL_Rect pacman_img;
	SDL_Rect dstrect;

	int pac_x, pac_y;

	std::tie(pac_x, pac_y) = pacman->Get_pose();
	// SDL_SetRenderDrawColor(sdl_renderer, 0, 100, 0, 100);
	Direction direct;
	direct = pacman->status;
	switch(direct){
		case Direction::up:
			img = SDL_LoadBMP("./../Image/pac_up.bmp");
			break;
		case Direction::down:
			img = SDL_LoadBMP("./../Image/pac_down.bmp");
			break;
		case Direction::left:
			img = SDL_LoadBMP("./../Image/pac_left.bmp");
			break;
		case Direction::right:
			img = SDL_LoadBMP("./../Image/pac_right.bmp");
			break;
	}
	
	texture = SDL_CreateTextureFromSurface(sdl_renderer, img);

	dstrect = {pac_y*10+10,pac_x*10+10,30,30};
	SDL_RenderCopy(sdl_renderer, texture, NULL, &dstrect);

	// pacman_img.w = 30;
	// pacman_img.h = 30;
	// pacman_img.y = pac_x*10+10;
	// pacman_img.x = pac_y*10+10;
	// SDL_RenderFillRect(sdl_renderer, &pacman_img);

	SDL_Rect enemy_img;
	int enemy_x, enemy_y;
	for (int num=0 ; num<4 ; num++){
		
		std::tie(enemy_x, enemy_y) = enemy_group.at(num)->Get_pose();
		switch(num){
			case 0:
				img = SDL_LoadBMP("./../Image/enem1.bmp");
				break;
			case 1:
				img = SDL_LoadBMP("./../Image/enem2.bmp");
				break;
			case 2:
				img = SDL_LoadBMP("./../Image/enem3.bmp");
				break;
			case 3:
				img = SDL_LoadBMP("./../Image/enem5.bmp");
				break;
		}

		texture = SDL_CreateTextureFromSurface(sdl_renderer, img);

		dstrect = {enemy_y*10+10,enemy_x*10+10,30,30};
		SDL_RenderCopy(sdl_renderer, texture, NULL, &dstrect);

		// SDL_SetRenderDrawColor(sdl_renderer, 1*num, 50*(num+1), 1*num, 100);
		// enemy_img.w = 30;
		// enemy_img.h = 30;
		// enemy_img.y = enemy_x*10+10;
		// enemy_img.x = enemy_y*10+10;
		// SDL_RenderFillRect(sdl_renderer, &enemy_img);
		
	}

	SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
	// std::string title{"Game Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
	// SDL_SetWindowTitle(sdl_window, title.c_str());
}

