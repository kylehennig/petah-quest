#ifndef DRAW_H
#define DRAW_H

#include "entity.h"
#define CHUNK_WIDTH 92 //will 80
#define CHUNK_HEIGHT 24 //will 24

void draw_map_at(struct map *map, uint32_t x, uint32_t y);
void draw_entities_screen(struct entity_list *list, uint32_t x, uint32_t y);
void draw_map_character(struct map *map, /*uint32_t screenDestx, uint32_t screenDesty,*/ uint32_t mapX, uint32_t mapY);

void dedraw_entity(struct entity *ent);
void draw_entity(struct entity *ent);

void do_flash(uint32_t x, uint32_t y);

#endif
