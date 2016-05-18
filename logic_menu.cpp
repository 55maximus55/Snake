#include "logic_menu.h"

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
