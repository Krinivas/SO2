#include "Sheep.h"

std::mutex Sheep::moveMutex;
std::mutex Sheep::drawStateMutex;
Sheep::Sheep(	std::vector<std::vector<Field>>* tableField,
                int positionY,
                int positionX,
                int number) :_tableField(tableField),
                                _positionY(positionY),
                                _positionX(positionX),
								_number(number),
                                _foodActual(foodDefault),
                                _died(false){
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
    if((*_tableField)[_positionY][_positionX]._grassLevel == 0)
        move();
		drawState();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                             
    }
}

void Sheep::move(){
    moveMutex.lock();
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
    moveMutex.unlock();
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


void Sheep::die(){
    _died = true;
}

std::string Sheep::getName(){
    return _name;
}

bool Sheep::isDied(){
    return _died;
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
void Sheep::moveUp(){
    if( _positionY - 1 >= 0) 
        if((*_tableField)[_positionY-1][_positionX]._unit==nullptr){
            (*_tableField)[_positionY-1][_positionX]._unit=this;
            (*_tableField)[_positionY][_positionX]._unit=nullptr;
            (*_tableField)[_positionY][_positionX].drawColored();
            (*_tableField)[_positionY-1][_positionX].drawColored();
            _positionY--;
        }
}


void Sheep::moveDown(){
    if( _positionY + 1 < (*_tableField).size()) 
        if((*_tableField)[_positionY+1][_positionX]._unit==nullptr){
            (*_tableField)[_positionY+1][_positionX]._unit=this;
            (*_tableField)[_positionY][_positionX]._unit=nullptr;
            (*_tableField)[_positionY][_positionX].drawColored();
            (*_tableField)[_positionY+1][_positionX].drawColored();
            _positionY++;
        }
}
void Sheep::moveRight(){
    if( _positionX + 1 < (*_tableField).size()) 
        if((*_tableField)[_positionY][_positionX+1]._unit==nullptr){
            (*_tableField)[_positionY][_positionX+1]._unit=this;
            (*_tableField)[_positionY][_positionX]._unit=nullptr;
            (*_tableField)[_positionY][_positionX].drawColored();
            (*_tableField)[_positionY][_positionX+1].drawColored();
            _positionX++;
        }
}
void Sheep::moveLeft(){
    if( _positionX - 1 >= 0) 
        if((*_tableField)[_positionY][_positionX-1]._unit==nullptr){
            (*_tableField)[_positionY][_positionX-1]._unit=this;
            (*_tableField)[_positionY][_positionX]._unit=nullptr;
            (*_tableField)[_positionY][_positionX].drawColored();
            (*_tableField)[_positionY][_positionX-1].drawColored();
            _positionX--;
        }
}

std::string Sheep::getState(){
	if (_foodActual >= 0&& _foodActual <= 9)
		return "Sheep number: " + getName() + " Food:  " + std::to_string(_foodActual);
	else
		return "Sheep number: " + getName() + " Food: " + std::to_string(_foodActual);

}

int Sheep::getActualFood(){
	return _foodActual;
}

void Sheep::drawState(){
	drawStateMutex.lock();
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvprintw(_number, (*_tableField).size()*2 + 5, getState().c_str());
	attroff(COLOR_PAIR(3));
	drawStateMutex.unlock();
}