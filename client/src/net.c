#include "net.h"
#include <unistd.h>


int handshake(struct map *map, char ch, int sockfd) {
    write(sockfd, ch, sizeof(char));
    if (read(sockfd, &map->width, sizeof(uint32_t)) == 0) {
        exit();
    }
    if (read(sockfd, &map->height, sizeof(uint32_t)) == 0) {
        exit();
    }

    map->map = malloc(map->height*map->width);
    if (read(sockfd, map->map, map->height*map->width) == 0) {
        exit();
    }
}
