#include "Field.h"
#include <string>


std::mutex Field::grassMutex;
bool Field::isEndOfTheWorld = false;


Field::Field() : _grassLevel(startGrass), _unit(nullptr)
{
	_sign = "aa";
   _runThread = std::thread(&Field::run, this);
}


Field::~Field()
{
	
}

void Field::setPosition(int y, int x){
	_positionX = x;
	_positionY = y;
}

void Field::drawColored(){ 
    grassMutex.lock();
    if(_unit == nullptr){
        init_color(COLOR_GREEN, 0 , 1000 * _grassLevel / (maxGrass + 1), 0);
		init_pair(_grassLevel + 5, COLOR_GREEN, COLOR_GREEN);
		attron(COLOR_PAIR(_grassLevel + 5));
		_sign[0]++;
		_sign[1]++;
        mvprintw(_positionY, _positionX*2 , _sign.c_str());
		attroff(COLOR_PAIR(_grassLevel + 5));
    }
    else{
        init_color(COLOR_RED, 0 , 1000 * _grassLevel / (maxGrass + 1), 0);
		if (_unit->isDead()){
			init_pair(4, COLOR_BLACK, COLOR_RED);
			attron(COLOR_PAIR(4));
			mvprintw(_positionY, _positionX * 2, _unit->getName().c_str());
			attroff(COLOR_PAIR(4));
		}            
		else{
			init_pair(2, COLOR_WHITE, COLOR_RED);
			attron(COLOR_PAIR(2));
			mvprintw(_positionY, _positionX * 2, _unit->getName().c_str());
			attroff(COLOR_PAIR(2));
		}
		


    }
    refresh();
    grassMutex.unlock();
}

void Field::setSign(std::string sign){
	_sign = sign;
}

void Field::run(){
	while (!isEndOfTheWorld){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        if(_grassLevel < maxGrass){
            _grassLevel++;
        }
		drawColored();
		if (_sign[0] == 'z')
			_sign == "aa";

    }
}


int Field::getGrassLevel(){
    return _grassLevel;
}
