#include "Sheep.h"
#include "Field.h"



Sheep::Sheep(std::vector<std::vector<Field>>* tableField,
                int positionY,
                int positionX,
                int number) : Unit(tableField,positionY,positionX, number) {

	_foodActual = foodDefault;
    _name = "S" + std::to_string(number);
    _runThread = std::thread(&Sheep::run, this);
}


Sheep::~Sheep()
{
}

void Sheep::run(){
    while(!_died){
		_foodActual--;
		if(_foodActual < foodMax)
			eat();
		if((*_tableField)[_positionY][_positionX]._grassLevel < 3)
			move();
		drawState();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
	drawState();
}

void Sheep::move(){
	unitMutex.lock();
    _foodActual--;
    if( isMoveUpBest() )
        moveUp();
    else if (isMoveDownBest())
        moveDown();
    else if (isMoveLeftBest())
        moveLeft();
    else if (isMoveRightBest())
        moveRight();
	refresh();
	unitMutex.unlock();
}
void Sheep::eat(){
    if((*_tableField)[_positionY][_positionX]._grassLevel > 1){
        (*_tableField)[_positionY][_positionX]._grassLevel-=2;
        _foodActual+=3;
    }
    else
        if(_foodActual < 0)
            die();
}





int Sheep::getGrassUp(){
    if( _positionY - 1 < 0)
        return 0;
    else
        if((*_tableField)[_positionY-1][_positionX]._unit!=nullptr)
            return 0;
    return (*_tableField)[_positionY-1][_positionX].getGrassLevel();
}
int Sheep::getGrassDown(){
    if( _positionY + 1 >= (*_tableField).size())
        return 0;
    else
        if((*_tableField)[_positionY+1][_positionX]._unit!=nullptr)
            return 0;
    return (*_tableField)[_positionY+1][_positionX].getGrassLevel();
}
int Sheep::getGrassLeft(){
    if( _positionX - 1 < 0)
        return 0;
    else
        if((*_tableField)[_positionY][_positionX-1]._unit!=nullptr)
            return 0;
    return (*_tableField)[_positionY][_positionX-1].getGrassLevel();
}
int Sheep::getGrassRight(){
    if( _positionX + 1 >= (*_tableField).size())
        return 0;
    else
        if((*_tableField)[_positionY][_positionX+1]._unit!=nullptr)
            return 0;
    return (*_tableField)[_positionY][_positionX+1].getGrassLevel();
}


bool Sheep::isMoveUpBest(){
    return (getGrassUp() >= getGrassDown() &&
            getGrassUp() >= getGrassLeft() &&
            getGrassUp() >= getGrassRight() &&
            getGrassUp() > 0);
}
bool Sheep::isMoveDownBest(){
    return (getGrassDown() >= getGrassUp() &&
            getGrassDown() >= getGrassLeft() &&
            getGrassDown() >= getGrassRight() &&
            getGrassDown() > 0);
}
bool Sheep::isMoveRightBest(){
    return (getGrassRight() >= getGrassDown() &&
            getGrassRight() >= getGrassLeft() &&
            getGrassRight() >= getGrassUp() &&
            getGrassRight() > 0);
}
bool Sheep::isMoveLeftBest(){
    return (getGrassLeft() >= getGrassDown() &&
            getGrassLeft() >= getGrassUp() &&
            getGrassLeft() >= getGrassRight()&&
            getGrassLeft() > 0);
}

std::string Sheep::getState(){
	std::string out;
	if (_foodActual >= 0 && _foodActual <= 9)
		out = "Sheep: " + Unit::getName() + " Food:  " + std::to_string(_foodActual);
	else
		out = "Sheep: " + Unit::getName() + " Food: " + std::to_string(_foodActual);

	if (_died)
		out += " IS DEAD";
	else
		out += "        ";
	return out;

}


void Sheep::drawState(){
	drawStateMutex.lock();
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvprintw(_number, (*_tableField).size() * 2 + 5, getState().c_str());
	attroff(COLOR_PAIR(3));
	drawStateMutex.unlock();
}

std::string Sheep::getType(){
	return "sheep";
}