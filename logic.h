#ifndef LOGIC_H
#define LOGIC_H

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define CELL_EMPTY 0
#define CELL_SNAKE 1
#define CELL_FOOD 2

#define GAME_SIZE 20
#define START_SNAKE_SIZE 5

struct Fr{
    int x;
    int y;
};

struct Game {
    int **cells;
    int head_x, head_y;
    int head_dir;
    int snake_size;
    int food_x, food_y;
    int count_freecells;
    Fr freecells[GAME_SIZE*GAME_SIZE];
};

void game_init();
void game_count_freecells(Game &game);
void game_main (Game &game);

void menu_main (Game &game);
void menu_help ();

#endif // LOGIC_H
