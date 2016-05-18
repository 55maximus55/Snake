#include "logic.h"

#include <windows.h>
#include <ctime>

#include "render.h"

void game_init(){
    srand(time(NULL));
    draw_logo();
    Sleep(2000);
    Game game;
    game.win = 0;
    game.head_x = GAME_SIZE / 2;
    game.head_y = GAME_SIZE / 2;
    game.head_dir = RIGHT;
    game.snake_size = START_SNAKE_SIZE;
    game.score = 0;

    game.cells = new int*[GAME_SIZE];
    for (int i = 0; i < GAME_SIZE; i++) {
        game.cells[i] = new int[GAME_SIZE];
    }
    for (int y = 0; y < GAME_SIZE; y++){
        for (int x = 0; x < GAME_SIZE; x++){
            game.cells[x][y] = CELL_EMPTY;
        }
    }
    for (int x = game.head_x - 4; x <= game.head_x; x++){
        game.cells[x][game.head_y] = CELL_SNAKE;
    }
    game_create_food(game);
    menu_main (game);
}

void game_count_freecells(Game &game){
    int count = 0;
    for (int y = 0; y < GAME_SIZE; y++){
        for (int x = 0; x < GAME_SIZE; x++){
            if (game.cells[x][y] == CELL_EMPTY){
                game.freecells[count].x = x;
                game.freecells[count].y = y;
                count++;
            }
        }
    }
    game.count_freecells = count;
}

void game_create_food(Game &game){
    game_count_freecells(game);
    if (game.count_freecells == 0){
        game.win = 1;
    }
    else {
        int a = rand() % game.count_freecells;
        game.cells[game.freecells[a].x][game.freecells[a].y] = CELL_FOOD;
    }
}

void game_main (Game &game){
    bool end = 0;
    do {
        draw_game(game);
    } while (end == 0);
}

void menu_main (Game &game){
    int cursor = 0;
    draw_main_menu(cursor);
    do {
        if (GetAsyncKeyState(VK_UP) != 0){
            if (cursor == 0){
                cursor = 2;
            }
            else {
                cursor--;
            }
            draw_main_menu(cursor);
        }
        if (GetAsyncKeyState(VK_DOWN) != 0){
            if (cursor == 2){
                cursor = 0;
            }
            else {
                cursor++;
            }
            draw_main_menu(cursor);
        }
        if (GetAsyncKeyState(VK_RETURN) != 0){
            if (cursor == 0){
                game_main (game);
            }
            else if (cursor == 1){
                menu_help ();
            }
            else if (cursor == 2){
                cursor = 3;
            }
            draw_main_menu(cursor);
        }
        Sleep(50);
    } while (cursor != 3);
}

void menu_help(){

}
