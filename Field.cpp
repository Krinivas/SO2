#include "Field.h"
#include <string>


std::mutex Field::grassMutex;

Field::Field() : _grassLevel(startGrass), _unit(nullptr)
{
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
	init_color(COLOR_GREEN, 0 , 1000 * _grassLevel / maxGrass, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(_positionY, _positionX * 2, _sign.c_str());
	attroff(COLOR_PAIR(1));
    refresh();
}

void Field::setSign(std::string sign){
	_sign = sign;
}

void Field::run(){
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(_grassLevel < maxGrass)
            _grassLevel++;
        grassMutex.lock();
        drawColored();
        grassMutex.unlock();
    }
}
