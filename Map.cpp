#include "Map.h"




Map::Map(int size): _size(size){
	initscr();
    start_color();
	isEndOfTheWorld = false;
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
	isEndOfTheWorld = true;
	Field::isEndOfTheWorld = true;
	for (int y = 0; y < _size; y++){
		for (int x = 0; x < _size; x++){
			if (tableField[y][x]._unit != nullptr){
				tableField[y][x]._unit->_died = true;
				tableField[y][x]._unit->_runThread.detach();
			}
			tableField[y][x]._runThread.detach();
		}
	}
	for (int y = 0; y < underTakerThreads.size(); y++){
		underTakerThreads[y].detach();
	}
	endwin();
}

void Map::Spawn(){
	for (int i = 0; i < startSheepCount ; i++)
        spawnSheep(i);
	for (int i = 0; i < startWolfCount; i++)
		spawnWolf(i);
	refresh();
}

void Map::spawnSheep(int number){

	Unit::unitMutex.lock();
    int positionY, positionX;
    do{
    positionX = randomInt(1, _size-1);
    positionY = randomInt(1, _size-1);
    }while(tableField[positionY][positionX]._unit!=nullptr);
    tableField[positionY][positionX]._unit =
            new Sheep(&tableField, positionY, positionX, number);
	underTakerThreads.push_back(std::thread(&Map::underTaker, this, tableField[positionY][positionX]._unit));
	refresh();

	Unit::unitMutex.unlock();
}

void Map::spawnWolf(int number){

	Unit::unitMutex.lock();
	int positionY, positionX;
	do{
		positionX = randomInt(1, _size - 1);
		positionY = randomInt(1, _size - 1);
	} while (tableField[positionY][positionX]._unit != nullptr);
	tableField[positionY][positionX]._unit =
		new Wolf(&tableField, positionY, positionX, number);
	underTakerThreads.push_back(std::thread(&Map::underTaker, this, tableField[positionY][positionX]._unit));
	refresh();
	Unit::unitMutex.unlock();
}

int Map::randomInt(int from, int to){
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(from, to);
    return uniform_dist(e1);
}

void Map::underTaker(Unit* unit){
	while (!isEndOfTheWorld){
		if (unit->isDead()){
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			Unit::unitMutex.lock();
			int num = unit->_number;
			tableField[unit->_positionY][unit->_positionX]._unit = nullptr;
			Unit::unitMutex.unlock();
		/*	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			if (unit->getType()=="sheep")
				spawnSheep(num);
			if (unit->getType() == "wolf")
				spawnWolf(num);*/
		}
	}
}
