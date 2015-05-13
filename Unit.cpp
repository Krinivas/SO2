#include "Unit.h"
#include "Field.h"
std::mutex Unit::unitMutex;
std::mutex Unit::drawStateMutex;

Unit::Unit(std::vector<std::vector<Field>>* tableField,
	int positionY,
	int positionX,
	int number) :_tableField(tableField),
	_positionY(positionY),
	_positionX(positionX),
	_number(number),
	_died(false){
}


Unit::~Unit()
{
	_runThread.detach();
}

bool Unit::isDead(){
	return _died;
}

void Unit::die(){
	_died = true;
}

std::string Unit::getName(){
	return _name;
}



bool Unit::moveUp(){
	if (_positionY - 1 >= 0)
		if ((*_tableField)[_positionY - 1][_positionX]._unit == nullptr){
			(*_tableField)[_positionY - 1][_positionX]._unit = this;
			(*_tableField)[_positionY][_positionX]._unit = nullptr;
			(*_tableField)[_positionY][_positionX].drawColored();
			(*_tableField)[_positionY - 1][_positionX].drawColored();
			_positionY--;
			return true;
		}
	return false;
}


bool Unit::moveDown(){
	if (_positionY + 1 < (*_tableField).size())
		if ((*_tableField)[_positionY + 1][_positionX]._unit == nullptr){
			(*_tableField)[_positionY + 1][_positionX]._unit = this;
			(*_tableField)[_positionY][_positionX]._unit = nullptr;
			(*_tableField)[_positionY][_positionX].drawColored();
			(*_tableField)[_positionY + 1][_positionX].drawColored();
			_positionY++;
		return true;
		} 
	return false;
}
bool Unit::moveRight(){
	if (_positionX + 1 < (*_tableField).size())
		if ((*_tableField)[_positionY][_positionX + 1]._unit == nullptr){
			(*_tableField)[_positionY][_positionX + 1]._unit = this;
			(*_tableField)[_positionY][_positionX]._unit = nullptr;
			(*_tableField)[_positionY][_positionX].drawColored();
			(*_tableField)[_positionY][_positionX + 1].drawColored();
			_positionX++;
			return true;
		}
	return false;
}
bool Unit::moveLeft(){
	if (_positionX - 1 >= 0)
		if ((*_tableField)[_positionY][_positionX - 1]._unit == nullptr){
			(*_tableField)[_positionY][_positionX - 1]._unit = this;
			(*_tableField)[_positionY][_positionX]._unit = nullptr;
			(*_tableField)[_positionY][_positionX].drawColored();
			(*_tableField)[_positionY][_positionX - 1].drawColored();
			_positionX--;
			return true;
		}
	return false;
}

int Unit::getActualFood(){
	return _foodActual;
}

