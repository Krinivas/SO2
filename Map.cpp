#include "Map.h"


std::mutex Map::unitMutex;

Map::Map(int size): _size(size){
	initscr();
    start_color();
    for (int i = 0; i < _size; i++){
		tableField.push_back(std::vector<Field>(_size));
		for (int j = 0; j < _size; j++){
			tableField[i][j].setPosition(i,j);
			tableField[i][j].setSign("aa");
			tableField[i][j].drawColored();
    	}
	}
}

Map::~Map(){
	endwin();
	
}

void Map::Init(){
	for (int i = 0; i < startSheepCount ; i++)
        spawnSheep(i);

	refresh();
}

void Map::spawnSheep(int number){
    unitMutex.lock();
    int positionY, positionX;
    do{
    positionX = randomInt(0, _size-1);
    positionY = randomInt(0, _size-1);
    }while(tableField[positionY][positionX]._unit!=nullptr);
    tableField[positionY][positionX]._unit =
            new Sheep(&tableField, positionY, positionX, number);
    unitMutex.unlock();
}

int Map::randomInt(int from, int to){
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(from, to);
    return uniform_dist(e1);
}
