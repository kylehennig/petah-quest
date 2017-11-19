#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <poll.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "net.h"
#include "controller.h"


int main(int argc, char *argv[]) {
    struct sockaddr_in server;
    inet_pton(AF_INET, argv[1], &(server.sin_addr));
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    char ch = *argv[2];

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect(2)");
        exit(1);
    }

    struct map map;
    struct entity_list elist;
    elist.list = malloc(256*sizeof(struct entity));
    elist.size = 256;

    handshake(&map, ch, sock);

    struct pollfd fds[2] = {
        { .fd=STDIN_FILENO, .events=POLLIN | POLLPRI, .revents=0 },
        { .fd=sock,         .events=POLLIN | POLLPRI, .revents=0 }
    };

    while (1) {
        poll(fds, 2, -1);
        if (fds[0].revents & (POLLIN|POLLPRI)) {
            keyboard_controller(sock);
        } else if (fds[1].revents & (POLLIN|POLLPRI)) {
            server_controller(sock, &map, &elist);
        }
    }

    // initscr();
    // raw();
    // noecho();
    //
    //
    // endwin();
    return 0;
}
