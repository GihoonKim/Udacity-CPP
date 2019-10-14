#include "character.h"
#include <iostream>
#include "math.h"


std::tuple<int,int> Character::CurrentMap_pose(){

    int x = Character::pos_x/5;
    int y = Character::pos_y/5;

    return std::make_tuple(x,y);
}

Character::~Character(){

    for (size_t i=0; i<threads.size() ; i++){ threads[i].detach(); }

    // std::cout<<"character destruct"<<std::endl;
}

void Character::move(std::shared_ptr<Map> &map, Direction direct){

    int temp_x = Character::pos_x;
    int temp_y = Character::pos_y;

    switch(direct){
        case up:
            temp_x -= 1;
            break;
        case down:
            temp_x += 1;
            break;
        case left:
            temp_y -= 1;
            break;
        case right:
            temp_y += 1;
            break;
    }

    bool check = Valid_direction_check(map, temp_x, temp_y, direct);

    if(check){
        Character::pos_x = (temp_x+70) % 70;
        Character::pos_y = (temp_y+70) % 70;

        // std::cout<<"pos x is : "<<Character::pos_x <<" pos y is : "<<Character::pos_y<<std::endl;
    }
}

bool Character::Valid_direction_check(std::shared_ptr<Map> &map, int &x, int &y, Direction direct){

    std::vector<std::vector<GridPhase>> grid = map->Get_current_map();

    int check_x = 1;
    int check_y = 1;

    int grid_x = x/5;
    int grid_y = y/5;

    
    if(this->name == "pacman"){
        if ((x%5 !=0)&&(x%5 !=1)&&(x%5 !=4)) check_x += 1;
        if ((y%5 !=0)&&(y%5 !=1)&&(y%5 !=4)) check_y += 1;

        if ((x%5 ==4)) {grid_x +=1;}
        if ((y%5 ==4)) {grid_y +=1;}
    }
    else
    {
        
        if ((x%5 !=0)) check_x += 1;
        if ((y%5 !=0)) check_y += 1;
    }
    
    for (int i=0; i<check_x;i++){
        for (int j=0; j<check_y; j++){
            if ((grid[grid_x+i][grid_y+j]==occupied)|(grid[grid_x+i][grid_y+j]==laser)) return false;
        }
    }

    return true;

}
