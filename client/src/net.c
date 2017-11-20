#include "net.h"
#include <unistd.h>
#include <stdlib.h>


int handshake(struct map *map, char ch, uint32_t *id,int sockfd) {
    write(sockfd, &ch, sizeof(char));
    if (read(sockfd, &map->width, sizeof(uint32_t)) == 0) {
        exit(1);
    }
    if (read(sockfd, &map->height, sizeof(uint32_t)) == 0) {
        exit(1);
    }

    uint32_t to_read = map->height*map->width;
    map->map = malloc(to_read);
    for (int i = 0; i < to_read; i++) {
        if (read(sockfd, &map->map[i], sizeof(uint8_t)) == 0) {
            exit(1);
        }
    }
    read(sockfd, id, sizeof(uint32_t));
}


enum srv_cmd read_cmd(int sockfd) {
    uint8_t val;
    if(read(sockfd, &val, sizeof(uint8_t)) == 0) {
        exit(0);
    }
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

void get_text(int sockfd, uint32_t *len, char **str){
	read(sockfd, len, sizeof(uint32_t));
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


void send_move(int sockfd, enum dir dir) {
    uint8_t msg = MOVE_MASK | dir;
    write(sockfd, &msg, sizeof(uint8_t));
}


void send_action(int sockfd, enum dir dir) {
    uint8_t msg = ACTION_MASK | dir;
    write(sockfd, &msg, sizeof(uint8_t));
}


void send_switch(int sockfd, uint8_t weapon) {
    uint8_t msg = SWITCH_MASK | weapon;
    write(sockfd, &msg, sizeof(uint8_t));
}
