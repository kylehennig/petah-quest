#include "hud.h"
#include <ncurses.h>
#include "draw.h"


#define MAX_HEALTH 10

const char *weapons = ")}/-*!@O";

void draw_weapon_sel(uint8_t weapon) {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);


}


//takes in current health
void draw_health(uint8_t health){
  //how to do colors off of stack exchange
  start_color();
   // create foreground / background combination

   // turn color off
  //
  init_pair(8, COLOR_WHITE, COLOR_GREEN);
  init_pair(9, COLOR_WHITE, COLOR_RED);
  //draw health bars
  attron(COLOR_PAIR(8));
  for(uint8_t i = 0; i < health; i++){
   // use the above combination
   mvprintw(CHUNK_HEIGHT,i,"-");
  }
  attroff(COLOR_PAIR(8));

  //draw empty health bars
  attron(COLOR_PAIR(9));
  for(uint8_t i = health; i < MAX_HEALTH; i++){
    mvprintw(CHUNK_HEIGHT,i,"-");
  }
  attroff(COLOR_PAIR(9));
}

void show_text(char *txt, size_t len){


}
