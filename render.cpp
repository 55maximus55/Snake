#include "render.h"

#include <iostream>
#include <cstdlib>

#include "logic.h"

using namespace std;

void draw_game (Game &game){
    system("cls");
    cout << (char)(-55);
    for (int i = 0; i < GAME_SIZE; i++){
        cout << (char)(-51);
    }
    cout << (char)(-69) << endl;

    for (int y = 0; y < GAME_SIZE; y++){
        cout << (char)(-70);
        for (int x = 0; x < GAME_SIZE; x++){
            if (game.cells[x][y] == CELL_EMPTY){
                cout << ' ';
            }
            else if (game.cells[x][y] == CELL_FOOD){
                cout << (char)(4);
            }
            else if (game.cells[x][y] == CELL_SNAKE_HEAD){
                cout << (char)(1);
            }
            else {
                cout << (char)(-37);
            }
        }
        cout << (char)(-70) << endl;
    }

    cout << (char)(-56);
    for (int i = 0; i < GAME_SIZE; i++){
        cout << (char)(-51);
    }
    cout << (char)(-68) << endl;

    cout << "Size:  " << game.snake_size << endl;
}

void draw_logo(){
    system("cls");
    cout << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<' ' << (char)(-37) <<(char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) << endl;
    cout << (char)(-37) <<' ' << ' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<(char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << ' ' << (char)(-37) << endl;
    cout << (char)(-37) <<' ' << ' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) << endl;
    cout << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<' ' << (char)(-37) << ' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<(char)(-37) << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) << endl;
    cout << ' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<(char)(-37) <<' ' << ' ' << ' ' << ' ' << (char)(-37) << endl;
    cout << ' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) << endl;
    cout << ' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<(char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << (char)(-37) <<' ' << ' ' << (char)(-37) << endl;
    cout << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<(char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<' ' << ' ' << ' ' << (char)(-37) <<' ' << (char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) <<(char)(-37) << endl;
}

void draw_main_menu(int cursor){
    system("cls");
    cout << "Snake" << endl;
    if (cursor == 0){
        cout << (char)(4);
    }
    else {
        cout << ' ';
    }
    cout << "New game" << endl;
    if (cursor == 1){
        cout << (char)(4);
    }
    else {
        cout << ' ';
    }
    cout << "Help" << endl;
    if (cursor == 2){
        cout << (char)(4);
    }
    else {
        cout << ' ';
    }
    cout << "Exit" << endl;
}

void draw_help_menu(){
    system ("cls");
}

void draw_game_end (Game &game){
    system("cls");
    if (game.end_reason == END_GAME_OVER){
        cout << "Game over!" << endl;
        cout << "Your snake size: " << game.snake_size << endl;
    }
    else if (game.end_reason == END_WIN){
        cout << "You win!" << endl;
    }
    else {
        cout << "You leaved the game." << endl;
        cout << "Your snake size: " << game.snake_size << endl;
    }
}
