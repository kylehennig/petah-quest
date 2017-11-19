#include "hud.h"
#include <ncurses.h>
#include "draw.h"


#define MAX_HEALTH 10
#define NUM_WEAPONS 8

const char *weapons = ")}/-*!@O";

void draw_weapon_sel(uint8_t weapon) {
  start_color();
    init_pair(10, COLOR_WHITE, COLOR_BLACK);
    init_pair(11, COLOR_BLACK, COLOR_WHITE);

    //load whole white bar
    attron(COLOR_PAIR(10));
    for(int i = 0; i < NUM_WEAPONS; i++){
      mvaddch(CHUNK_HEIGHT,i+MAX_HEALTH,weapons[i]);

    }
    attroff(COLOR_PAIR(10));

    //load highlighted
    attron(COLOR_PAIR(11));
    mvaddch(CHUNK_HEIGHT,weapon+MAX_HEALTH,weapons[weapon]);
    attroff(COLOR_PAIR(10));
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

void show_text(char *txt){

  start_color();
	init_pair(14, COLOR_BLACK, COLOR_WHITE); // create foreground / background combination
	attron(COLOR_PAIR(14)); // use the above combination
  mvprintw(CHUNK_HEIGHT,NUM_WEAPONS+MAX_HEALTH,txt);
  attroff(COLOR_PAIR(14));


}
