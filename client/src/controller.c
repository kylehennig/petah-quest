#include "controller.h"
#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "net.h"
#include "draw.h"


void keyboard_controller(int sockfd) {
    char keypress = getchar();

    // switch (keypress) {
    //     case 'w':
    //         break;
    //     case 'a':
    //         break;
    // }
    printf("pressed %c\n", keypress);
}


void server_controller(int sockfd, struct map *map, struct entity_list *elist) {
    uint8_t cmd = read_cmd(sockfd);

    switch (cmd) {
        case FLASH: {
            uint32_t x, y;
            get_flash(sockfd, &x, &y);
            // do_flash();
            // refresh();
            printf("x: %i, y: %i\n", x, y);
            break;
        }
        case NEW: {
            uint32_t id, x, y;
            char ch;
            uint8_t colour;

            // dedraw_entity(&elist->list[id]);

            get_new(sockfd, &id, &x, &y, &ch, &colour);
            elist->list[id].x = x;
            elist->list[id].y = y;
            elist->list[id].ch = ch;
            elist->list[id].colour = colour;

            // draw_entity(&elist->list[id]);
            // refresh();
            printf("id: %i, x: %i, y: %i, ch: %c, colour: %i\n", id, x, y, ch, colour);
            break;
        }
        case DELETE: {
            uint32_t id;
            get_delete(sockfd, &id);
            printf("id: %i\n", id);
            break;
        }
        case TEXT: {
            uint32_t len;
            char *str;
            get_text(sockfd, &len, &str);
            printf("%s\n", str);
            free(str);
            break;
        }
        case MOVE: {
            uint32_t id, x, y;
            get_move(sockfd, &id, &x, &y);
            printf("id: %i, x: %i, y: %i\n", id, x, y);
            break;
        }
        case UPDATE: {
            uint32_t id;
            char ch;
            uint8_t colour;
            get_update(sockfd, &id, &ch, &colour);
            printf("id: %i, ch: %c, colour: %i\n", id, ch, colour);
            break;
        }
        case HEALTH: {
            uint8_t health;
            get_health(sockfd, &health);
            printf("health: %i\n", health);
            break;
        }
        default: {
            fprintf(stderr, "invalid server command %i\n", cmd);
            exit(1);
        }
    }
}
