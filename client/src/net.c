#include "net.h"
#include <unistd.h>
#include <stdlib.h>


int handshake(struct map *map, char ch, int sockfd) {
    write(sockfd, &ch, sizeof(char));
    if (read(sockfd, &map->width, sizeof(uint32_t)) == 0) {
        exit(1);
    }
    if (read(sockfd, &map->height, sizeof(uint32_t)) == 0) {
        exit(1);
    }

    map->map = malloc(map->height*map->width);
    if (read(sockfd, map->map, map->height*map->width) == 0) {
        exit(1);
    }
}


enum srv_cmd read_cmd(int sockfd) {
    uint8_t val;
    read(sockfd, &val, sizeof(uint8_t));
    return val;
}


//reads the first sizeof() bytes into variables left to right
void get_flash(int sockfd, uint32_t *x, uint32_t *y){
	read(sockfd, x, sizeof(uint32_t)); //should read x from sockfd
	read(sockfd, y, sizeof(uint32_t));
}

void get_new(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y, char *ch, uint8_t *colour){
	read(sockfd, id, sizeof(uint32_t));
	read(sockfd, x, sizeof(uint32_t));
	read(sockfd, y, sizeof(uint32_t));
    read(sockfd, ch, sizeof(char));
    read(sockfd, colour, sizeof(uint8_t));
}

void get_delete(int sockfd, uint32_t *id){
	read(sockfd, id, sizeof(uint32_t));
}

void get_text(int sockfd, size_t *len, char **str){
	read(sockfd, len, sizeof(size_t));
	*str = malloc(*len);
	read(sockfd, *str, *len);

}

void get_move(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y){
	read(sockfd, id, sizeof(uint32_t));
	read(sockfd, x, sizeof(uint32_t));
	read(sockfd, y, sizeof(uint32_t));
}

void get_update(int sockfd, uint32_t *id, char *ch, uint8_t *colour){
	read(sockfd, id, sizeof(uint32_t));
	read(sockfd, ch, sizeof(char));
	read(sockfd, colour, sizeof(uint8_t));

}

void get_health(int sockfd, uint8_t *health){
	read(sockfd, health, sizeof(uint8_t));
}
