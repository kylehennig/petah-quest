#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "entity.h"

void keyboard_controller(int sockfd);

void server_controller(int sockfd, struct map *map, struct entity_list *elist, uint32_t you);

#endif
