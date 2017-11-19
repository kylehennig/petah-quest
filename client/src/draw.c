#include <ncurses.h>
#include <stdint.h>
#include "draw.h"

//chunks
void draw_map_at(struct entity_list *list, uint32_t x, uint32_t y){


}

//draws a single character to the screen
//takes in coords from global map as well as where to draw the character to the screen
void draw_character(struct map *map, uint32_t screenDestx, uint32_t screenDesty, uint32_t mapX, uint32_t mapY){
	//get character from map
	//map.map is a 1D string
	uint32_t dest = mapX + (map->width)*mapY;
	char toBeLoaded = map->map[dest];
	//switch on character
	start_color();

	/*
	M   spikes          White on Black (1)
	~    lava           Black on Red (2)
	W    water          White on Blue (3)
	#    wall           White on Black (1)
	,    grass          green on black (4)
	.    stone          White on black (1)
	*/
	//        #    for           back
	init_pair(1,COLOR_WHITE, COLOR_BLACK); //stone wall spike
	init_pair(2,COLOR_BLACK, COLOR_RED); //lava
	init_pair(3,COLOR_WHITE, COLOR_BLUE); //water
	init_pair(4,COLOR_GREEN, COLOR_BLACK); //grass
	//wbkgd(WindowName, COLOR_PAIR(1))

	/*how to do colors off of stack exchange
	start_color();
	init_pair(1, COLOR_RED, COLOR_GREEN); // create foreground / background combination
	attron(COLOR_PAIR(1)); // use the above combination
	printw("Some text");
	attroff(COLOR_PAIR(1)); // turn color off
	*/

	switch (toBeLoaded){
		case 'M'://spikes
		attron(COLOR_PAIR(1));
		mvprintw(screenDesty,screenDestx,"M");
		attroff(COLOR_PAIR(1));
		refresh();
		break;

		case '~'://lava
		attron(COLOR_PAIR(2));
		mvprintw(screenDesty,screenDestx,"~");
		attroff(COLOR_PAIR(2));
		refresh();
		break;

		case 'W': //Water
		attron(COLOR_PAIR(3));
		mvprintw(screenDesty,screenDestx,"~");
		attroff(COLOR_PAIR(3));
		refresh();
		break;

		case '#': //wall
		attron(COLOR_PAIR(1));
		mvprintw(screenDesty,screenDestx," ");
		attroff(COLOR_PAIR(1));
		refresh();
		break;

		case ',': //grass
		attron(COLOR_PAIR(4));
		mvprintw(screenDesty,screenDestx,",");
		attroff(COLOR_PAIR(4));
		refresh();
		break;

		case '.': //stone
		attron(COLOR_PAIR(1));
		mvprintw(screenDesty,screenDestx,".");
		attroff(COLOR_PAIR(1));
		refresh();
		break;

		default:
		attron(COLOR_PAIR(1));
		mvprintw(screenDesty,screenDestx,"?");
		attroff(COLOR_PAIR(1));
		refresh();

		break;
	}//end switch

}


void draw_entities_screen(struct entity_list *list, uint32_t x, uint32_t y){


}

void redraw_entity(struct entity_list *list, uint32_t id){


}
