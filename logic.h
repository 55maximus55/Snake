#ifndef LOGIC_H
#define LOGIC_H

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define CELL_EMPTY 0
#define CELL_FOOD 1
#define CELL_SNAKE_UP 2
#define CELL_SNAKE_RIGHT 3
#define CELL_SNAKE_DOWN 4
#define CELL_SNAKE_LEFT 5
#define CELL_SNAKE_HEAD 6

#define GAME_SIZE 20
#define START_SNAKE_SIZE 5

#define END_GAME_OVER 0
#define END_WIN 1
#define END_EXIT 2

struct Fr{
    int x;
    int y;
};

struct Game {
    int **cells;
    int head_x, head_y;
    int end_x, end_y;
    int head_dir;
    int snake_size;
    int food_x, food_y;
    int count_freecells;
    int end_reason;
    bool end;
    Fr freecells[GAME_SIZE*GAME_SIZE];
};

void game_init();
void game_count_freecells (Game &game);
void game_main            (Game &game);
void game_create_food     (Game &game);
void game_control         (Game &game);
void game_pause           (Game &game);
void game_move            (Game &game);
void game_end             (Game &game);

void menu_main (Game &game);
void menu_help ();

#endif // LOGIC_H
