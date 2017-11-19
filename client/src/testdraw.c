#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "net.h"
#include "controller.h"
#include "draw.h"
#include "entity.h"
#include "hud.h"

//key definitions
#define LEFT               68
#define UP                 66
#define RIGHT              67
#define DOWN               65
#define ENTER_KEY          10


int main(int argc, char *argv[]) {


	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(false);
	clear();
	refresh();

	//included a fakemap
	struct map fakemap;
	fakemap.width = 260;
	fakemap.height = 96;
	fakemap.map = "t,,,,,,,t,,,,t,,,,,,,,,,t,,,,t,,,,,,,t,,,,,,,,,,t,,,,,,,,t,,,,,,,,,,,,,,,e,t,,,,,,,t,,,,,,,,,,,,,,,,,t,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,t,,,,t,e,,,t,,,,t,,,,,,,,,,,,t,,,,,,,,t,,,,,t,,,,,,e,,,t,,,,t,,,,,,,,,,,,,t,,,,,,,,t,,,,,,,t,,,,,,,,,t,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,t,,,e,,,,,,,,,,,,,,,,,,,t,,,,,t,,,,,,,t,,,,,,e,,,,,t,,,,,,,,,,,,,,,,t,t,,,,,,,,,,t,,,,,,,,t,,,,e,,,t,,,,,,e,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,t,,,t,,,,,t,,,,t,,,,,t,,,,,,,t,,,,,,t,,,,,,,,,,,,e,,t,,,,,,,,e,,,,,t,,,t,,,,,,t,,,,t,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,t,,,,,,,,,,,,,,,,,,,,,,e,,,#####################,,,t,,,,,,,,,t,,,,,,,,,,,,,,,,,t,,,,,t,,,,,t,,t,,,,,,t,,,t,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,a,,,,,,e,,,###################,,,,,,,,,,,,,,,,,,,#,,,,,,,t,,,,,,,,t,,,,t,,,,,,,,,t,,,,,,,,,,,,,,,,,,t,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########,,,,,,,,,#,,,,,,,,,,########,,,,,,,,,########################################,,,t,,,t,,,,,t,,,t,,,,t,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#####,,,,,,,#,,,,,,,,,,,,,,,,,,,,#,,,,,,#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,######,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#,,,#,,,,,,,,,,,,,,,,,#,,,,,,,,,,#,,,,,,#######,,,###############################,,,######,,,,,t,,,t,,,t,,,,,t,,,,e,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#,,,,,,,,,,,#,,,,,,,,,#,,,,,,,,,,#,,,,,,#,,,,,,,,,#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,######,,t,,,,t,,,,,,,,t,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#,,,#,,,,,,,#,,,,,,,,,#,,,,,,,,,,,,,,,,,#,#,#,#,#,#,#########################,,,##########,,,,,,,,,,,,,t,,,,,,,,,,,t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########################################,#,#,#,#,#,#,,,,,,,,,,,,,,,,,,,,,,,#,,,,,,,######,,,t,,,,t,,e,,,,,t,,,,t,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#,,,##,###,#,#,####,#,###,##,##,#############,#,,,,,,,,,,,,,,,,,,,,,,,#,,,##########,,,,,,,,,,,,,,,,,,,,,,,,,,,t,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#,,,,,,,,,,,#,,,,,,,,,,,,,,#,,,,,,,,#,,,,,#####,#,,,,,,,,,,,,,,,,,,,,,,,#,,,,,,,######,,,,,,,t,,,,,,,t,,,,,,,t,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#,,,,,,,,,,,,,,,,,,,#####,#######################,#,,,##########,,,t,,,,,,,,,,,,,,,t,,,,,,t,,t,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#####,,,,,,,,,,,,,,,,,,,,,,,,,#,,,,,,,######,,,,,,,,,,,t,,,,,,,,,,,t,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,#####,,,,,,,,,,,,,,,,,,,,,,,,##,,,##########,,,,,,,t,,,,,,,t,,t,,,,,,,,,t,,,,t,,##,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,,,,,,,,,,,,w,,,w,,,,,,,,,,,,,,,,,,,,,,,,###############################,,,,,,,,,,,##,,,t,,,,,,t,,,,,,,,,,,,,t,,,,,,,,e,,,##,,,,,,,,,,,,,,,,,,,,,,,,,##########,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,,,,,,,,w,,,,w,,,,,w,,,,,,,,,,,,,,,,,,,,,#######################################,,,##,,,,,,,t,,,,,,,,,,,t,,,,,,,,,t,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,,,,w,,,,,w,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,##,,,p,,,,,,,pM,,,M,,,,,,,,,,,p,,,,,,,#,,,##,,,,,,,,,,,,,,te,,,,,,,,,,,,,,,,,,t,,,,##,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,w,,,,,w,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,##pa,,,,MMMM,M,,M,,,,MMMMMMMMMM,,,,,,##,,,###########################,,,t,,,,,,,,,t,##,,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,p,,,p,M,p,M,,M,,,,,,,,,pdM,,,,,,,,,,,,,#########################,,,,e,,,,t,,,,,d##,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###############################,,,,,,,,,,,,,,,#############################################################,##,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,################################,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###############################,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########################################,##,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,################################,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,w,,,,,##,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,############################################,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,########,,,,,,,,########,###,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,,,,,################################################################,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###g,,,,,,,#,,,a,,,,#,,,,,,,g###,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,,,,,,##################################################################,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,#,,,,,,,,#,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,####################################################################,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,##########,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,h,,,,aWWWWWWWWWWWWWWWWWd,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWW,,,,,,,,,,,,,,,,g,,g,,,g,,,,,,,,,,,,g,,,,,,,,,,,,###,,,,,,,,,,,,h,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,p,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,h,,,,,,,,,WWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWW,,,,,,,,,,,,WWWWWWWWWWWWWWWWW,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWW,,,,,,WWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,g,,g,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##############,,,,##############,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWWWW,,,,,,,,,,WWWWWWWWWWWW,,,,,,,,,,,,,,,,WWWWWWWWWWWWWWWW,,,,,,,,,,,,g,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,#,,,,#,,,,,,,,,,###,,,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,,,,,,###,,,,,,,,g,#,,,,#,g,,,,,,,,###,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,g,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,g,,,,,,###,,,,,,,,,,#,,,,#,,,,,,,,,,###,,,,,,,,,,,,,w,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,,,,,###,,,,,,,,,,#,,,,#,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,g,,g,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,###,,g,,g,,,,#,,,,#,,,,g,,g,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,g,,,,,#,,,,#,,,,,g,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,#,,,,#,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,##############,,,,##############,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,............,,,,,,,,g,,g,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,####,,,##################,,,####,,,,,,,,,,,,,,,,,,,,,,............,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########,,,,,,,,,,,,,,,,,g,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,...........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#MMMMMMM#############################################################################################################...#############MMMMMMM#,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,g,,,g,,,,,,,,g,,,g,,,###,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#MMMMMMM#############################################################################################################...#############MMMMMMM#,,,,,,,,,,,,,,,g,,,,g,,,,,,###,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#MMMMMMM#...........................................................................................................#...#...........#MMMMMMM#,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,g,,,,,g,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,g,,,,,,,,,,,,,,,,,,,,,,#########......###################...............................................................................####...####........#########,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,###,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,g,g,,,,,,,,,,,,,,,,,,,,,,,,###.........#........#........#...............................................................................#.........#...........###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,######################,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###.........#........#........#............###########################################........................#.........#...........###,,,,,,,,,,,,,,,,,,,,,,,,,g,,,g,,,,####################,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###.........#........#........#............#...................##....................#........................#.........#...........###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,####,,g,,,,g,,####,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###.........######...#...######............#...................##....................#........................####...####...........###,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,####,,,g,,g,,,####,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###............................................................##...................................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,####,,,,,,,,,,####,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###............................................................##...................................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,#######,,,,#######,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###............................................................##...................................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,######,,,,######,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###........................................#...................##....................#..............................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,,,,,##,,,,##,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###........................................#...................##....................#..............................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,g,,,,,,,,g,,,,,,,,,,,,,,,,,,w,,,w,,w,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#################.....#...................##....................#........###################...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#.....######...#########################...######..........................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,w,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#.....#.........................................#........#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#.....#.........................................#........#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#.....#.........................................#........#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,,w,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#.....#.........................................#........#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,w,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#.....####################...####################........#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#........................................#...#...........................#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#........................#...#...........................#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#........................#...#...........................#.................#...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............#........................#...#...........................###################...................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#################...................######...######............................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###......................................................#.............#............................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###......................................................#.............#............................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###......................................................#.............#......................#...################..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,a,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................##################..................#.............#......................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..................#..d..........#......................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............##########...##########..................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............#.....................#..................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............#.....................#..................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#...............................#.....................#..................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............#.....................#..................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............#.....................#..................#..................#..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............#.....................#..................####################..................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................#................#..............#..........P..........#........................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WWW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###..................##################..............#######################........................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,WW,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,###.................................................................................................................................###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,W,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########...........................................................................................................................#########,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#MMMMMMM#...........................................................................................................................#MMMMMMM#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#MMMMMMM#############################################################################################################################MMMMMMM#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#MMMMMMM#############################################################################################################################MMMMMMM#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,#########,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";

	//draw_map_at(&fakemap,50,50);//player co-ords, map auto drawn
	uint32_t x = 126;//sweet spot on spwn
	uint32_t y = 84;
	draw_health(4);
	show_text("You shall fail. -Gerbo");
	draw_weapon_sel(NSTAR);



	while(true){
		int cha = getch();
		//printf("%d\n",cha);
		if(cha == LEFT){
			x--;
			draw_map_at(&fakemap,x,y);
		}
		if(cha == UP){
			y++;
			draw_map_at(&fakemap,x,y);

		}
		if(cha == DOWN){
			y--;
			draw_map_at(&fakemap,x,y);
		}
		if(cha == RIGHT){
			x++;
			draw_map_at(&fakemap,x,y);
		}
		if(cha == ENTER_KEY){
			break;
		}

		//draw char
		start_color();
		init_pair(6, COLOR_YELLOW, COLOR_RED); // create foreground / background combination
		attron(COLOR_PAIR(6)); // use the above combination
		mvprintw(y % CHUNK_HEIGHT,x % CHUNK_WIDTH,"A");
		attroff(COLOR_PAIR(6)); // turn color off
		refresh();
	}

	//map loaded
	//*map, screenDestx, screenDesty, mapX, mapY
/*
	for(uint32_t i = 0; i< fakemap.width-20; i++){
		for(uint32_t j = 0; j < fakemap.height; j++){
			draw_character(&fakemap, i,j,i,j);


		}

	}
	*/

	refresh();
	while(true){}
	endwin();

  return 0;
}
