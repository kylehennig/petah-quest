#include "controller.h"
#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "net.h"
#include "draw.h"
#include "hud.h"


void keyboard_controller(int sockfd) {
    char keypress = getch();

    if (keypress >= '1' && keypress <= '8') {
        draw_weapon_sel(keypress - '1');
        refresh();
        send_switch(sockfd, keypress - '1');
    } else {
        switch (keypress) {
            case 'w':
                send_move(sockfd, NORTH);
                break;
            case 'a':
                send_move(sockfd, WEST);
                break;
            case 's':
                send_move(sockfd, SOUTH);
                break;
            case 'd':
                send_move(sockfd, EAST);
                break;

            case 'i':
                send_action(sockfd, NORTH);
                break;
            case 'j':
                send_action(sockfd, WEST);
                break;
            case 'k':
                send_action(sockfd, SOUTH);
                break;
            case 'l':
                send_action(sockfd, EAST);
                break;
        }
    }
}


void server_controller(int sockfd, struct map *map, struct entity_list *elist, uint32_t you) {
    uint8_t cmd = read_cmd(sockfd);

    switch (cmd) {
        case FLASH: {
            uint32_t x, y;
            get_flash(sockfd, &x, &y);
            do_flash(x, y, &elist->list[you]);
            refresh();
            printf("x: %i, y: %i\n", x, y);
            break;
        }
        case NEW: {
            uint32_t id, x, y;
            char ch;
            uint8_t colour;

            if (id >= elist->size) {
                size_t new_size = elist->size * ELIST_FACTOR;
                elist->list = realloc(elist->list, new_size * sizeof(struct entity));
                elist->size = new_size;
            }

            get_new(sockfd, &id, &x, &y, &ch, &colour);
            elist->list[id].x = x;
            elist->list[id].y = y;
            elist->list[id].ch = ch;
            elist->list[id].colour = colour;

            draw_ent_scr(&elist->list[id], &elist->list[you]);

            if (id == you) {
                draw_map_at(map, elist->list[you].x, elist->list[you].y);
                draw_entities_screen(elist, &elist->list[you]);
            }

            refresh();
            break;
        }
        case DELETE: {
            uint32_t id;
            get_delete(sockfd, &id);
            elist->list[id].ch = 0;
            draw_mapch_scr(map, elist->list[id].x, elist->list[id].y, &elist->list[you]);
            refresh();
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

            draw_mapch_scr(map, elist->list[id].x, elist->list[id].y, &elist->list[you]);

            uint32_t oldx = elist->list[id].x;
            uint32_t oldy = elist->list[id].y;
            elist->list[id].x = x;
            elist->list[id].y = y;

            draw_ent_scr(&elist->list[id], &elist->list[you]);

            if (id == you && (x/CHUNK_WIDTH != oldx/CHUNK_WIDTH || y/CHUNK_HEIGHT != oldy/CHUNK_HEIGHT)) {
                draw_map_at(map, elist->list[you].x, elist->list[you].y);
                draw_entities_screen(elist, &elist->list[you]);
            }
            refresh();
            break;
        }
        case UPDATE: {
            uint32_t id;
            char ch;
            uint8_t colour;
            get_update(sockfd, &id, &ch, &colour);

            elist->list[id].ch = ch;
            elist->list[id].colour = colour;

            draw_ent_scr(&elist->list[id], &elist->list[you]);
            refresh();
            break;
        }
        case HEALTH: {
            uint8_t health;
            get_health(sockfd, &health);

            draw_health(health);
            refresh();
            break;
        }
        default: {
            endwin();
            fprintf(stderr, "invalid server command %i\n", cmd);
            exit(1);
        }
    }
}
