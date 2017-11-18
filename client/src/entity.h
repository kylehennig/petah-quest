#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <stddef.h>

struct entity {
    int32_t x;
    int32_t y;
    char ch;
    uint8_t colour;
};

struct map {
    uint32_t width;
    uint32_t height;
    char *map;
};

struct entity_list {
    struct entity *elist;
    size_t size;
    size_t alloc_size;
};


void draw_map_at(struct entity_list *list, uint32_t x, uint32_t y);
void draw_entities_screen(struct entity_list *list, uint32_t x, uint32_t y);

void redraw_entity(struct entity_list *list, uint32_t id);

#endif
