#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

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

    write(sock, "hello\n", 6);

    struct map map;
    struct entity_list *elist = malloc(256*sizeof(struct entity_list));

    handshake(&map, ch, sock);

    while (1) {
        server_controller(sock, &map, elist);
    }

    // initscr();
    // raw();
    // noecho();
    //
    //
    // endwin();
    return 0;
}
