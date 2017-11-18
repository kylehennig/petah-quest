#include "controller.h"
#include <unistd.h>
#include "net.h"
#include "draw.h"
#include <ncurses.h>


void server_controller(int sockfd, struct map *map, struct entity_list *elist) {
    enum srv_cmd cmd = read_cmd(sockfd);

    switch (cmd) {
        case FLASH:
            uint32_t x, y;
            get_flash(sockfd, &x, &y);
            do_flash();
            refresh();
            break;
        case NEW:
            uint32_t id, x, y;
            char ch;
            uint8_t colour;

            dedraw_entity(&elist->list[id]);

            get_new(int sockfd, &id, &x, &y, &ch, &colour);
            elist->list[id]->x = x;
            elist->list[id]->y = y;
            elist->list[id]->ch = ch;
            elist->list[id]->colur = colour;

            draw_entity(&elist->list[id]);
            refresh();
            break;

    }
}
