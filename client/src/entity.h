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

#define ELIST_FACTOR 2

struct entity_list {
    struct entity *list;
    size_t size;
};

#endif
