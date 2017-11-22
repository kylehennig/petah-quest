#ifndef RESIZE_H
#define REZIZE_H

#include <stdint.h>
#include "entity.h"

void resize_set_you(int32_t you);
void resize_set_elist(struct entity_list *elist);
void resize_set_map(struct map *map);

void resize_handler(int signo);

#endif
