#include "textbox.c"
#include <ncurses.h>
#include "hud.h"

const char *_text = NULL;
size_t _len = 0;
size_t _idx;


void set_hud_text(const char *text, size_t len) {
    _text = text;
    _len = len;
    _idx = 0;
}


void write_hud_text() {
    init_pair(14, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(14));

    mvaddnstr((LINES-1), NUM_WEAPONS+MAX_HEALTH+padded, );
}
