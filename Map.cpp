#include "Map.h"



Map::Map(int rozmiar): _rozmiar(rozmiar){
	initscr();
    start_color();
    for (int i = 0; i < _rozmiar; i++){
		tableField.push_back(std::vector<Field>(_rozmiar));
		for (int j = 0; j < _rozmiar; j++){
			tableField[i][j].setPosition(i,j);
			tableField[i][j].setSign("- ");
			tableField[i][j].drawColored();
    	}
	}
}

Map::~Map(){
	endwin();
	
}

void Map::Init(){
	for (int i = 0; i < _rozmiar; i++)
		for (int j = 0; j < _rozmiar*2; j+=2)
//			mvprintw(i, j, "-");

	refresh();
}
