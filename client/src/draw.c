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
	init_pair(20,COLOR_WHITE,COLOR_WHITE);//white
	//wbkgd(WindowName, COLOR_PAIR(1))

	/*how to do colors off of stack exchange
	start_color();
	init_pair(1, COLOR_RED, COLOR_GREEN); // create foreground / background combination
	attron(COLOR_PAIR(1)); // use the above combination
	printw("Some text");
	attroff(COLOR_PAIR(1)); // turn color off
	*/

	if (mapX > map->width || mapX < 0 || mapY > map->height || mapY < 0) {
		init_pair(1,COLOR_WHITE, COLOR_BLACK);
		mvaddch(screenDesty, screenDestx ,' ');

		return;
	}


	switch (toBeLoaded){
		case 'M'://spikes
		attron(COLOR_PAIR(1));
		mvprintw(screenDesty,screenDestx,"M");
		attroff(COLOR_PAIR(1));
		break;

		case '~'://lava
		attron(COLOR_PAIR(2));
		mvprintw(screenDesty,screenDestx,"~");
		attroff(COLOR_PAIR(2));
		break;

		case 't'://lava
		attron(COLOR_PAIR(4));
		mvprintw(screenDesty,screenDestx,"%%");
		attroff(COLOR_PAIR(4));
		break;

		case 'W': //Water
		attron(COLOR_PAIR(3));
		mvprintw(screenDesty,screenDestx,"~");
		attroff(COLOR_PAIR(3));
		break;

		case '#': //wall
		attron(COLOR_PAIR(20));
		mvaddch(screenDesty,screenDestx,' ');
		attroff(COLOR_PAIR(20));
		break;

		case ',': //grass
		attron(COLOR_PAIR(4));
		mvprintw(screenDesty,screenDestx,",");
		attroff(COLOR_PAIR(4));
		break;

		case '.': //stone
		attron(COLOR_PAIR(1));
		mvprintw(screenDesty,screenDestx,".");
		attroff(COLOR_PAIR(1));
		break;

		default:
		attron(COLOR_PAIR(4));
		mvprintw(screenDesty,screenDestx,",");
		attroff(COLOR_PAIR(4));
		break;
	}//end switch

}

//draw entity ONLY IF entity is on player screen
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


		start_color();
		init_pair(30+color, color, COLOR_BLACK); //COLOR WILL THROW ERROR
		attron(COLOR_PAIR(30+color)); // use the above combination
		mvaddch(screenDesty,screenDestx,c);
		attroff(COLOR_PAIR(30+color)); // turn color off
}


void draw_ent_scr(struct entity *ent, struct entity *player) {
	uint32_t x_low = player->x - player->x % CHUNK_WIDTH;
	uint32_t x_high = x_low + CHUNK_WIDTH;
	uint32_t y_low = player->y - player->y % CHUNK_HEIGHT;
	uint32_t y_high = y_low + CHUNK_HEIGHT;

	if (ent->x >= x_low && ent->x < x_high && ent->y >= y_low && ent->y < y_high) {
		draw_entity(ent);
	}
}


void draw_mapch_scr(struct map *map, uint32_t mapX, uint32_t mapY, struct entity *player) {
	uint32_t x_low = player->x - player->x % CHUNK_WIDTH;
	uint32_t x_high = x_low + CHUNK_WIDTH;
	uint32_t y_low = player->y - player->y % CHUNK_HEIGHT;
	uint32_t y_high = y_low + CHUNK_HEIGHT;

	if (mapX >= x_low && mapX < x_high && mapY >= y_low && mapY < y_high) {
		draw_map_character(map, mapX, mapY);
	}
}


void draw_entities_screen(struct entity_list *list, struct entity *player) {
	for (size_t i = 0; i < list->size; ++i) {
		if (list->list[i].ch != 0) {
			draw_ent_scr(&list->list[i], player);
		}
	}
}
