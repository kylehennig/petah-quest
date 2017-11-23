#include "hud.h"
#include <ncurses.h>
#include "draw.h"

#define MAX_HEALTH 20
#define NUM_WEAPONS 8
#define padded 2

const char *weapons = ")}/-*!@O";

void draw_weapon_sel(uint8_t weapon) {
  start_color();
    init_pair(10, COLOR_WHITE, COLOR_BLACK);
    init_pair(11, COLOR_BLACK, COLOR_WHITE);

    //load whole white bar
    attron(COLOR_PAIR(10));
    mvaddch((LINES-1),MAX_HEALTH,' ');
    for(int i = 0; i < NUM_WEAPONS; i++){
      mvaddch((LINES-1),i+MAX_HEALTH+1,weapons[i]);
    }
    mvaddch((LINES-1),MAX_HEALTH+1+NUM_WEAPONS,' ');
    attroff(COLOR_PAIR(10));

    //load highlighted
    attron(COLOR_PAIR(11));
    mvaddch((LINES-1),weapon+MAX_HEALTH+1,weapons[weapon]);
    attroff(COLOR_PAIR(10));
}


//takes in current health
void draw_health(uint8_t health){
  //how to do colors off of stack exchange
  start_color();
  init_pair(8, COLOR_WHITE, COLOR_GREEN);
  init_pair(9, COLOR_WHITE, COLOR_RED);
  //draw health bars
  attron(COLOR_PAIR(8));
  for(uint8_t i = 0; i < health/5; i++){
   // use the above combination
   mvprintw((LINES-1),i,"-");
  }
  attroff(COLOR_PAIR(8));

  //draw empty health bars
  attron(COLOR_PAIR(9));
  for(uint8_t i = health/5; i < MAX_HEALTH; i++){
    mvprintw((LINES-1),i,"-");
  }
  attroff(COLOR_PAIR(9));
}

void show_text(char *txt){
  start_color();
	init_pair(14, COLOR_BLACK, COLOR_WHITE); // create foreground / background combination
	attron(COLOR_PAIR(14)); // use the above combination
  mvprintw((LINES-1),NUM_WEAPONS+MAX_HEALTH+padded,txt);
  attroff(COLOR_PAIR(14));
}
