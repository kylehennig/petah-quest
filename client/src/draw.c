#include <ncurses.h>
#include <stdint.h>
#include "draw.h"
#include "entity.h"

//renders a chunk
void draw_map_at(struct map *map,uint32_t x, uint32_t y){

	//find the coords of the map based off player coords
	uint32_t mapTopLeftX = x-x%CHUNK_WIDTH;
	uint32_t mapTopLeftY = y-y%CHUNK_HEIGHT;

	//draws a chunk given the top left co-ordinates
	for(uint32_t i = mapTopLeftX; i< mapTopLeftX+CHUNK_WIDTH; i++){
		for(uint32_t j = mapTopLeftY; j < mapTopLeftY+CHUNK_HEIGHT; j++){
			draw_map_character(map,i,j);
		}

	}
}

//draws a single character to the screen
//takes in coords from global map as well as where to draw the character to the screen
void draw_map_character(struct map *map, /*uint32_t screenDestx, uint32_t screenDesty, */uint32_t mapX, uint32_t mapY){
	//get character from map
	//map.map is a 1D string
	uint32_t dest = mapX + (map->width)*mapY;
	char toBeLoaded = map->map[dest];

	//DONT WANT TO PASS IN A SCREEN DEST
	uint32_t mapTopLeftX = mapX-mapX%CHUNK_WIDTH; //top left of the map
	uint32_t mapTopLeftY = mapY-mapY%CHUNK_HEIGHT; //top right of the map
	uint32_t screenDestx = mapX - mapTopLeftX;
	uint32_t screenDesty = mapY - mapTopLeftY;

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
	init_pair(5,COLOR_BLACK, COLOR_YELLOW);
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

		case 't'://lava
		attron(COLOR_PAIR(4));
		mvprintw(screenDesty,screenDestx,"%%");
		attroff(COLOR_PAIR(4));
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
		mvprintw(screenDesty,screenDestx,"#");
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
		attron(COLOR_PAIR(5));
		mvprintw(screenDesty,screenDestx,"?");
		attroff(COLOR_PAIR(5));
		refresh();

		break;
	}//end switch

}

//draws an entitie at a specified map location
void draw_entities_screen(struct entity_list *list, uint32_t x, uint32_t y){

}


void draw_entity(struct entity *ent){


	int32_t mapX = ent->x;
	int32_t mapY = ent->y;
	char c = ent->ch;
	uint8_t color = ent->colour;

	//DONT WANT TO PASS IN A SCREEN DEST
	uint32_t mapTopLeftX = mapX-mapX%CHUNK_WIDTH; //top left of the map
	uint32_t mapTopLeftY = mapY-mapY%CHUNK_HEIGHT; //top right of the map
	uint32_t screenDestx = mapX - mapTopLeftX;
	uint32_t screenDesty = mapY - mapTopLeftY;

	//how to do colors off of stack exchange
	start_color();
	init_pair(16, color, COLOR_BLACK); //COLOR WILL THROW ERROR
	attron(COLOR_PAIR(16)); // use the above combination
	mvaddch(screenDesty,screenDestx,c);
	attroff(COLOR_PAIR(16)); // turn color off

}
