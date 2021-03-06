#ifndef RENDER_H
#define RENDER_H

#include "logic.h"

void draw_game (Game &game);

void draw_logo();
void draw_main_menu(int cursor);
void draw_game_end (Game &game);
void draw_pause    (Game &game, int cursor);

#endif // RENDER_H
