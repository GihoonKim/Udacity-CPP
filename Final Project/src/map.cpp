#include<iostream>
#include<thread>
#include<mutex>

#include "map.h"


Map::Map()
	{
		grid.resize(GridSize,std::vector<GridPhase>(GridSize, GridPhase::food));
		Map::initialize();
	}


void Map::initialize()
{
	// Generate Map with block
	int temp[GridSize][GridSize]
	{{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,0,0,0,1,0,1,1,0,1,0,0,0,1},
	 {1,0,1,0,0,0,0,0,0,0,0,1,0,1},
	 {1,0,1,1,1,0,1,1,0,1,1,1,0,1},
	 {1,0,1,0,0,0,0,0,0,0,0,1,0,1},
	 {1,0,1,1,0,1,0,0,1,0,1,1,0,1},
	 {0,0,0,0,0,1,0,0,1,0,0,0,0,0},
	 {1,1,1,1,0,1,0,0,1,0,1,1,1,1},
	 {1,0,0,0,0,1,1,1,1,0,0,0,0,1},
	 {1,0,1,1,0,0,0,0,0,0,1,1,0,1},
	 {1,0,1,1,1,0,1,1,0,1,1,1,0,1},
	 {1,0,1,0,0,0,1,0,0,0,0,1,0,1},
	 {1,0,0,0,1,1,1,0,1,1,0,0,0,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for(int x=0 ; x<GridSize ; x++){
		for(int y=0 ; y<GridSize ; y++){

			if(temp[x][y]==1) { grid[x][y] = GridPhase::occupied; }
		}
	}

	threads.emplace_back(&Map::Add_laser,this);
	threads.emplace_back(&Map::Add_reverser,this);

	std::cout<<"map initialize end"<<std::endl;
	// for(int x=6; x<8 ; x++){
	// 	for(int y=6; y<8 ; y++){
	// 		grid[x][y] = GridPhase::empty;
	// 	}
	// }

}

void Map::Add_laser(){
	

	grid[5][7]=GridPhase::laser;
	grid[5][6]=GridPhase::laser;

  std::hash<std::thread::id> hasher;
  srand((unsigned int)hasher(std::this_thread::get_id()));
  // srand(time(NULL));
  double cycle_duration = (rand()%2000 + 5000);
  // _light_messages.is_block = false;
  //init stop watch
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  lastUpdate = std::chrono::system_clock::now();
  
  while(true){

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    
    if (timeSinceLastUpdate >= cycle_duration){

			
		while(true){
			
			if(Map::check_pos()) break;
		}

      std::lock_guard<std::mutex> Lock(_mutex);
			
      if (grid[5][6]==GridPhase::laser){
        	
				grid[5][6]=GridPhase::empty;
				grid[5][7]=GridPhase::empty;
      }
      else{
        grid[5][6]=GridPhase::laser;
				grid[5][7]=GridPhase::laser;
      }
      // _light_messages.send(std::move(_currentPhase));
      
      lastUpdate = std::chrono::system_clock::now();  
    }
  }

}

void Map::Add_reverser(){

	std::hash<std::thread::id> hasher;
	srand((unsigned int)hasher(std::this_thread::get_id()));
	// srand(time(NULL));
	int waiting_time = (rand()%5000 + 10000);
	
	std::this_thread::sleep_for(std::chrono::milliseconds(waiting_time));

	int temp_x_pac = 40;
	int temp_y_pac = 5;

	_mutex.lock();
	Map::grid[8][1] = GridPhase::reverser;
	_mutex.unlock();

	// threads.emplace_back(&Map::
	//Use condition variable

}


	

bool Map::check_pos(){


	for (int i=0; i<5; i++){

		if (pos[i][0]>20 && pos[i][0]<30 && pos[i][1]>25 && pos[i][1]<40){
			return false;
		}
	}

	return true;
}

void Map::Change_map(GridPhase status){
	
	int pac_x_map = (Map::pos[0][0]+2.5)/5;
	int pac_y_map = (Map::pos[0][1]+2.5)/5;
	
	if (Map::grid[pac_x_map][pac_y_map]==GridPhase::food | Map::grid[pac_x_map][pac_y_map]==GridPhase::reverser){
		std::lock_guard<std::mutex> Lock(_mutex);
		Map::grid[pac_x_map][pac_y_map] = status;
	}
}