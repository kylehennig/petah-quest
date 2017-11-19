#ifndef NET_H
#define NET_H

#include "entity.h"
#include <stdint.h>

enum srv_cmd {
    FLASH, NEW, DELETE, TEXT, MOVE, UPDATE, HEALTH
};

int handshake(struct map *map, char ch, int sockfd);

enum srv_cmd read_cmd(int sockfd);

void get_flash(int sockfd, uint32_t *x, uint32_t *y);
void get_new(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y, char *ch, uint8_t *colour);
void get_delete(int sockfd, uint32_t *id);
void get_text(int sockfd, size_t *len, char **str);
void get_move(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y);
void get_update(int sockfd, uint32_t *id, char *ch, uint8_t *colour);
void get_health(int sockfd, uint8_t *health);

enum dir {NORTH, EAST, SOUTH, WEST};

#define MOVE 0b00010000
void send_move(int sockfd, enum dir dir);
#define ACTION 0b00100000
void send_action(int sockfd, enum dir dir);

#endif
