#ifndef HUD_H
#define HUD_H

#include <stdint.h>

void draw_weapon_sel(uint8_t weapon);
void draw_health(uint8_t health);
void show_text(char *txt, size_t len);

#endif
