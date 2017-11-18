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
void get_new(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y);
void get_delete(int sockfd, uint32_t *id);
void get_text(int sockfd, size_t len, char **str);
void get_move(int sockfd, uint32_t *id, uint32_t *x, uint32_t *y);
void get_update(int sockfd, uint32_t *id, char *ch, uint8_t colour);
void get_health(int sockfd, uint8_t health);



#endif
