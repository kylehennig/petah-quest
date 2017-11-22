#include "resize.h"
#include <signal.h>
#include <ncurses.h>
#include "draw.h"


int32_t _rs_you;
struct entity_list *_rs_elist;
struct map *_rs_map;


void resize_set_you(int32_t you) {
    _rs_you = you;
}

void resize_set_elist(struct entity_list *elist) {
    _rs_elist = elist;
}

void resize_set_map(struct map *map) {
    _rs_map = map;
}


void resize_handler(int signo) {
    if (signo == SIGWINCH) {
        endwin();
        clear();
        refresh();

        draw_map_at(_rs_map, _rs_elist->list[_rs_you].x, _rs_elist->list[_rs_you].y);
        draw_entities_screen(_rs_elist, &_rs_elist->list[_rs_you]);
        refresh();
    }
}
