#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <poll.h>
#include <signal.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "net.h"
#include "controller.h"
#include "hud.h"
#include "resize.h"


int main(int argc, char *argv[]) {
    struct sockaddr_in server;

    if (argc < 4) {
        fputs("useage: ./pquest <ip> <port> <character>\n", stderr);
        exit(1);
    }

    inet_pton(AF_INET, argv[1], &(server.sin_addr));
    server.sin_family = AF_INET;
    int port = atoi(argv[2]);
    server.sin_port   = htons(port);

    char ch = *argv[3];

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect(2)");
        exit(1);
    }

    struct map         map;
    struct entity_list elist;
    elist.list = malloc(256 * sizeof(struct entity));
    elist.size = 256;

    uint32_t you;

    handshake(&map, ch, &you, sock);

    struct pollfd fds[2] = {
        { .fd = STDIN_FILENO, .events = POLLIN | POLLPRI, .revents = 0 },
        { .fd = sock,         .events = POLLIN | POLLPRI, .revents = 0 }
    };

    resize_set_you(you);
    resize_set_map(&map);
    resize_set_elist(&elist);
    signal(SIGWINCH, &resize_handler);


    initscr();
    //raw();
    curs_set(0);
    noecho();

    draw_weapon_sel(7);
    resize_set_weapon(7);

    while (1) {
        poll(fds, 2, -1);
        if (fds[0].revents & (POLLIN | POLLPRI)) {
            keyboard_controller(sock);
        }
        else if (fds[1].revents & (POLLIN | POLLPRI)) {
            server_controller(sock, &map, &elist, you);
        }
    }

    endwin();
    return(0);
}
