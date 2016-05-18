#include "logic.h"

#include <windows.h>

void game_init(){
    Game game;
    game.head_x = GAME_SIZE / 2;
    game.head_y = GAME_SIZE / 2;
    game.head_dir = RIGHT;
    game.snake_size = START_SNAKE_SIZE;

    game.cells = new int*[GAME_SIZE];
    for (int i = 0; i < GAME_SIZE; i++) {
        game.cells[i] = new int[GAME_SIZE];
    }
    for (int x = game.head_x - 4; x <= game.head_x; x++){
        game.cells[x][game.head_y];
    }
    game_count_freecells(game);
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

void game_main (Game &game){

}

void menu_main (Game &game){
    int cursor = 0;
    do {
        if (VK_UP != 0){
            if (cursor == 0){
                cursor = 2;
            }
            else {
                cursor--;
            }
        }
        if (VK_DOWN != 0){
            if (cursor == 2){
                cursor = 0;
            }
            else {
                cursor++;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) != 0){
            if (cursor == 0){
                game_main (game);
            }
            else if (cursor == 1){
                menu_help ();
            }
            else if (cursor == 3){
                cursor = 4;
            }
        }
    } while (cursor != 4);
}

void menu_help(){

}
