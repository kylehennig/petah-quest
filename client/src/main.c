#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
#include <arpa/inet.h>


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

    // initscr();
    // raw();
    // noecho();
    //
    //
    // endwin();
    return 0;
}
