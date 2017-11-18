#include "controller.h"
#include <unistd.h>
#include "net.h"
#include "draw.h"


void server_controller(int sockfd, struct map *map, struct entity_list *elist) {
    enum srv_cmd cmd = read_cmd(sockfd);

    switch (cmd) {
        case FLASH:
            uint32_t x, y;
            get_flash(sockfd, &x, &y);
            do_flash();
            break;
        case NEW:
            uint32_t id, x, y;
            char ch;
            uint8_t colour;
            get_new(int sockfd, &id, &x, &y, &ch, &colour);
            elist->list[id]->x = x;
            elist->list[id]->y = y;
            elist->list[id]->ch = ch;
            elist->list[id]->colur = colour;
            redraw_entity(elist, &id);

    }
}
