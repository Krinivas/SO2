// Farma.cpp : Defines the entry point for the console application.
//


#include "Map.h"
#include <iostream>
#include "curses.h"


int main(int argc, char* argv[])
{

    //initscr();
    //start_color();
    //if(can_change_color() == FALSE){
    //    endwin();
    //    printf("Your terminal does not support color\n");
    //    exit(1);
    //}
    Map mapa(20);
	mapa.Spawn();
	while(getch()!='q');
	return 0;

}

