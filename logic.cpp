#include "logic.h"

#include <windows.h>
#include <ctime>

#include "render.h"

void game_init(){
    srand(time(NULL));
    draw_logo();
    Sleep(4000);
    Game game;
    game.end = 0;
    game.speed = 5;
    game.head_x = GAME_SIZE / 2;
    game.head_y = GAME_SIZE / 2;
    game.head_dir = RIGHT;
    game.snake_size = START_SNAKE_SIZE;
    game.end_x = game.head_x - START_SNAKE_SIZE + 1;
    game.end_y = game.head_y;

    game.cells = new int*[GAME_SIZE];
    for (int i = 0; i < GAME_SIZE; i++) {
        game.cells[i] = new int[GAME_SIZE];
    }
    for (int y = 0; y < GAME_SIZE; y++){
        for (int x = 0; x < GAME_SIZE; x++){
            game.cells[x][y] = CELL_EMPTY;
        }
    }
    for (int x = game.head_x - 4; x < game.head_x; x++){
        game.cells[x][game.head_y] = CELL_SNAKE_RIGHT;
    }
    game.cells[game.head_x][game.head_y] = CELL_SNAKE_HEAD;

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
        game.end = 1;
        game.end_reason = END_WIN;
    }
    else {
        int a = rand() % game.count_freecells;
        game.cells[game.freecells[a].x][game.freecells[a].y] = CELL_FOOD;
    }
}

void game_main (Game &game){
    draw_game(game);
    do {
        game_control(game);
        Sleep(game.speed * 50);
    } while (game.end == 0);
    game_end(game);
}

void game_control(Game &game){
    int ctrl = -1;
    if (GetAsyncKeyState(VK_UP) != 0){
        ctrl = UP;
    }
    if (GetAsyncKeyState(VK_RIGHT) != 0){
        ctrl = RIGHT;
    }
    if (GetAsyncKeyState(VK_DOWN) != 0){
        ctrl = DOWN;
    }
    if (GetAsyncKeyState(VK_LEFT) != 0){
        ctrl = LEFT;
    }
    if (GetAsyncKeyState(VK_ESCAPE) != 0){
        game_pause (game);
    }

    if (ctrl == UP && game.head_dir != DOWN){
        game.head_dir = UP;
    }
    else if (ctrl == RIGHT && game.head_dir != LEFT){
        game.head_dir = RIGHT;
    }
    else if (ctrl == DOWN && game.head_dir != UP){
        game.head_dir = DOWN;
    }
    else if (ctrl == LEFT && game.head_dir != RIGHT){
        game.head_dir = LEFT;
    }

    game_move (game);
}

void game_pause(Game &game){
    int cursor = 0;
    bool pause = 1;
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState(VK_RETURN);
    draw_pause(game, cursor);
    do {
        if (GetAsyncKeyState(VK_UP) != 0){
            if (cursor == 0){
                cursor = 2;
            }
            else {
                cursor --;
            }
            draw_pause(game, cursor);
        }
        if (GetAsyncKeyState(VK_DOWN) != 0){
            if (cursor == 2){
                cursor = 0;
            }
            else {
                cursor++;
            }
            draw_pause(game, cursor);
        }
        if (GetAsyncKeyState(VK_LEFT) != 0){
            if (cursor == 1 && game.speed < 10){
                game.speed++;
                draw_pause(game, cursor);
            }
        }
        if (GetAsyncKeyState(VK_RIGHT) != 0){
            if (cursor == 1 && game.speed > 1){
                game.speed--;
                draw_pause(game, cursor);
            }
        }
        if (GetAsyncKeyState(VK_RETURN) != 0){
            if (cursor == 0){
                pause = 0;
            }
            else if (cursor == 2){
                pause = 0;
                game.end = 1;
                game.end_reason = END_EXIT;
            }
        }
        Sleep(50);
    } while (pause == 1);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_ESCAPE);
}

void game_move (Game &game){
    bool eat = 0;
    if (game.head_dir == UP){
        if (game.head_y == 0){
            if (game.cells[game.head_x][GAME_SIZE - 1] == CELL_EMPTY){
                game.cells[game.head_x][GAME_SIZE - 1] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_UP;
            }
            else if (game.cells[game.head_x][GAME_SIZE - 1] == CELL_FOOD){
                game.cells[game.head_x][GAME_SIZE - 1] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_UP;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_y = GAME_SIZE - 1;
        }
        else {
            if (game.cells[game.head_x][game.head_y - 1] == CELL_EMPTY){
                game.cells[game.head_x][game.head_y - 1] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_UP;
            }
            else if (game.cells[game.head_x][game.head_y - 1] == CELL_FOOD){
                game.cells[game.head_x][game.head_y - 1] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_UP;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_y--;
        }
    }
    else if (game.head_dir == RIGHT){
        if (game.head_x == GAME_SIZE - 1){
            if (game.cells[0][game.head_y] == CELL_EMPTY){
                game.cells[0][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_RIGHT;
            }
            else if (game.cells[0][game.head_y] == CELL_FOOD){
                game.cells[0][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_RIGHT;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_x = 0;
        }
        else {
            if (game.cells[game.head_x + 1][game.head_y] == CELL_EMPTY){
                game.cells[game.head_x + 1][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_RIGHT;
            }
            else if (game.cells[game.head_x + 1][game.head_y] == CELL_FOOD){
                game.cells[game.head_x + 1][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_RIGHT;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_x++;
        }
    }
    else if (game.head_dir == DOWN){
        if (game.head_y == GAME_SIZE - 1){
            if (game.cells[game.head_x][0] == CELL_EMPTY){
                game.cells[game.head_x][0] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_DOWN;
            }
            else if (game.cells[game.head_x][0] == CELL_FOOD){
                game.cells[game.head_x][0] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_DOWN;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_y = 0;
        }
        else {
            if (game.cells[game.head_x][game.head_y + 1] == CELL_EMPTY){
                game.cells[game.head_x][game.head_y + 1] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_DOWN;
            }
            else if (game.cells[game.head_x][game.head_y + 1] == CELL_FOOD){
                game.cells[game.head_x][game.head_y + 1] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_DOWN;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_y++;
        }
    }
    else {
        if (game.head_x == 0){
            if (game.cells[GAME_SIZE - 1][game.head_y] == CELL_EMPTY){
                game.cells[GAME_SIZE - 1][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_LEFT;
            }
            else if (game.cells[GAME_SIZE - 1][game.head_y] == CELL_FOOD){
                game.cells[GAME_SIZE - 1][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_LEFT;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_x = GAME_SIZE - 1;
        }
        else {
            if (game.cells[game.head_x - 1][game.head_y] == CELL_EMPTY){
                game.cells[game.head_x - 1][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_LEFT;
            }
            else if (game.cells[game.head_x - 1][game.head_y] == CELL_FOOD){
                game.cells[game.head_x - 1][game.head_y] = CELL_SNAKE_HEAD;
                game.cells[game.head_x][game.head_y] = CELL_SNAKE_LEFT;
                eat = 1;
                game.snake_size++;
                game_create_food(game);
            }
            else {
                eat = 1;
                game.end = 1;
                game.end_reason = END_GAME_OVER;
            }
            game.head_x--;
        }
    }

    if (eat == 0){
        if (game.cells[game.end_x][game.end_y] == CELL_SNAKE_UP){
            if (game.end_y == 0){
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_y = GAME_SIZE - 1;
            }
            else {
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_y--;
            }
        }
        else if (game.cells[game.end_x][game.end_y] == CELL_SNAKE_RIGHT){
            if (game.end_x == GAME_SIZE - 1){
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_x = 0;
            }
            else {
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_x++;
            }
        }
        else if (game.cells[game.end_x][game.end_y] == CELL_SNAKE_DOWN){
            if (game.end_y == GAME_SIZE - 1){
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_y = 0;
            }
            else {
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_y++;
            }
        }
        else {
            if (game.end_x == 0){
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_x = GAME_SIZE - 1;
            }
            else {
                game.cells[game.end_x][game.end_y] = CELL_EMPTY;
                game.end_x--;
            }
        }
    }
    draw_game(game);
}

void game_end (Game &game){
    draw_game_end (game);
    Sleep(5000);
    game.end = 0;
    game.head_x = GAME_SIZE / 2;
    game.head_y = GAME_SIZE / 2;
    game.head_dir = RIGHT;
    game.snake_size = START_SNAKE_SIZE;
    game.end_x = game.head_x - START_SNAKE_SIZE + 1;
    game.end_y = game.head_y;
    for (int y = 0; y < GAME_SIZE; y++){
        for (int x = 0; x < GAME_SIZE; x++){
            game.cells[x][y] = CELL_EMPTY;
        }
    }
    for (int x = game.head_x - 4; x < game.head_x; x++){
        game.cells[x][game.head_y] = CELL_SNAKE_RIGHT;
    }
    game.cells[game.head_x][game.head_y] = CELL_SNAKE_HEAD;
    game_create_food(game);
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
                GetAsyncKeyState(VK_UP);
                GetAsyncKeyState(VK_RIGHT);
                GetAsyncKeyState(VK_DOWN);
                GetAsyncKeyState(VK_LEFT);
                GetAsyncKeyState(VK_ESCAPE);
                game_main (game);
                GetAsyncKeyState(VK_UP);
                GetAsyncKeyState(VK_DOWN);
                GetAsyncKeyState(VK_RETURN);
            }
            else if (cursor == 1){
                menu_help ();
                GetAsyncKeyState(VK_UP);
                GetAsyncKeyState(VK_DOWN);
                GetAsyncKeyState(VK_RETURN);
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
