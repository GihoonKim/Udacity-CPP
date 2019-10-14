## Introduction

- Just one round pacman game
- pacman game with following functions

    1) make some block periodically change between `empty` and `laser`

    2) move Enemy to pursue pacman (Just simple heuristic algorithm)

    3) If pacman eat  `reverser` which appear a specific time, pacman can make enemy destroy

    during effect are going.

    4) If pacman eat all coin or destroy all enemies, you win and game terminate.

    5) If pacman is caught by  enemy, you lose and game terminate.

## Structure

- `Main` function
    - Creates a `controller`, `game`, `render` object.
    - Main call `game::run` to start game loop
    - Main call `game::end_game` to display game over state(win or lose)
- `Game`
    - Stores a `Pacman`, `Enemy`, `Map` Object
    - At `game::run` , run `controller::HandleInput` and `update`
    - `game::update` update `pacman` and `enemy`'s location information which managed by `Map` Object

- controller
    - `controller::handleInput` get keyboard input and move pacman if possible direction.
    - `Enemy`
        - When this object is called in `Game`, occur thread which run `Enemy::control`
        - `Enemy::control` conduct pursuing pacman function in the while loop with specific frequency

- `Map`
    - `Map::Add_laser` add laser into specific blocks with designed time interval.
    - `Map::Add_reverser` make reverser on map and notify if pacman eat the reverser.

## Launch

- cd `build` → `cmake ..` → `make` → `./Pacman`
