#ifndef DRAW_H
#define DRAW_H

#include "entity.h"
#define CHUNK_WIDTH 80
#define CHUNK_HEIGHT 24

void draw_map_at(struct map *map, uint32_t x, uint32_t y);
void draw_entities_screen(struct entity_list *list, struct entity *player);
void draw_map_character(struct map *map, uint32_t mapX, uint32_t mapY);
void draw_entity(struct entity *ent);

void draw_ent_scr(struct entity *ent, struct entity *player);
void draw_mapch_scr(struct map *map, uint32_t mapX, uint32_t mapY, struct entity *player);

void do_flash(uint32_t x, uint32_t y);

#endif
