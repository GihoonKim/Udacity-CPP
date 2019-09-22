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
	 {1,0,1,0,0,0,0,0,0,0,0,1,0,1},
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
