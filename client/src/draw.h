#ifndef DRAW_H
#define DRAW_H

#include "entity.h"

void draw_map_at(struct entity_list *list, uint32_t x, uint32_t y);
void draw_entities_screen(struct entity_list *list, uint32_t x, uint32_t y);

void redraw_entity(struct entity_list *list, uint32_t id);

#endif
