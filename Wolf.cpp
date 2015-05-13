#include "Wolf.h"
#include "Field.h"



Wolf::Wolf(std::vector<std::vector<Field>>* tableField,
	int positionY,
	int positionX,
	int number) : Unit(tableField, positionY, positionX, number) {

	_foodActual = foodDefault;
	_name = "W" + std::to_string(number);
	_runThread = std::thread(&Wolf::run, this);
}


Wolf::~Wolf()
{
	_died = true;
}

void Wolf::run(){
	while (!_died){
		_foodActual--;
		if (_foodActual < foodMax)
			hunt();
		if (_foodActual < 0)
			_died = true;
		drawState();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	drawState();
}


void Wolf::hunt(){
	unitMutex.lock();
	Sheep* closestSheep = findClosestSheep();
	if (closestSheep != nullptr){
		moveToClosestSheep(closestSheep);
		tryToKillDatSheep(closestSheep);
	}
	unitMutex.unlock();
}

std::string Wolf::getState(){
	std::string out;
	if (_foodActual >= 0 && _foodActual <= 9)
		out = "Wolf: " + Unit::getName() + " Food:  " + std::to_string(_foodActual);
	else
		out = "Wolf: " + Unit::getName() + " Food: " + std::to_string(_foodActual);
	if (_died)
		out += " IS DEAD";
	else
		out += "        ";
	return out;
}

void Wolf::drawState(){
	drawStateMutex.lock();
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvprintw(_number + (*_tableField).size()+ 2, 0, getState().c_str());
	attroff(COLOR_PAIR(3));
	drawStateMutex.unlock();
}

std::string Wolf::getType(){
	return "wolf";
}

Sheep* Wolf::findClosestSheep(){
	int distance = 3 * _tableField->size();
	Sheep* closestSheep = nullptr;
	for (int y = 0; y < _tableField->size(); y++)
		for (int x = 0; x < _tableField->size(); x++)
			if ((*_tableField)[y][x]._unit != nullptr)
				if ((*_tableField)[y][x]._unit->getType() == "sheep")
					if ((abs(this->_positionY - y) + abs(this->_positionX - x)) < distance)
						if (!(*_tableField)[y][x]._unit->isDead()){
						closestSheep = dynamic_cast<Sheep*>((*_tableField)[y][x]._unit);
						distance = (abs(this->_positionY - y) + abs(this->_positionX - x));
					}
	return closestSheep;
}

void Wolf::moveToClosestSheep(Sheep* closestSheep) {
	if (closestSheep == nullptr)
		return;
	if (closestSheep->_positionY < this->_positionY){
		if (!moveUp())
			if (closestSheep->_positionX < this->_positionX){
				if (!moveLeft())
					if (!moveDown())
						if (!moveRight())
							return;
			}
			else{
				if (!moveRight())
					if (!moveDown())
						if (!moveLeft())
							return;
			}
		
	}
	else if (closestSheep->_positionY == this->_positionY){
		if (closestSheep->_positionX < this->_positionX){
			if (!moveLeft())
				if (!moveDown())
					if (!moveRight())
						return;
		}
		else{
			if (!moveRight())
				if (!moveDown())
					if (!moveLeft())
						return;
		}
	} 
	else {
		if (!moveDown())
			if (closestSheep->_positionX < this->_positionX){
			if (!moveLeft())
				if (!moveUp())
					if (!moveRight())
						return;
			}
			else{
				if (!moveRight())
					if (!moveUp())
						if (!moveLeft())
							return;
			}
	}
}

void Wolf::tryToKillDatSheep(Sheep* closestSheep){
	if (_positionY - 1 >= 0)
		if ((*_tableField)[_positionY - 1][_positionX]._unit == closestSheep){
			killDatSheep(closestSheep);
			return;
		}
	if (_positionY + 1 < (*_tableField).size())
		if ((*_tableField)[_positionY + 1][_positionX]._unit == closestSheep){
			killDatSheep(closestSheep);
			return;
		}
	if (_positionX - 1 >= 0)
		if ((*_tableField)[_positionY][_positionX - 1]._unit == closestSheep){
			killDatSheep(closestSheep);
			return;
		}
	if (_positionX + 1 < (*_tableField).size())
		if ((*_tableField)[_positionY][_positionX + 1]._unit == closestSheep){
			killDatSheep(closestSheep);
			return;
		}
	
}

void Wolf::killDatSheep(Sheep* closestSheep){
	_foodActual += 20 + closestSheep->_foodActual;
	closestSheep->die();
	
}