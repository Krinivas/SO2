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
}

void Wolf::run(){
	while (!_died){
		_foodActual--;
		if (_foodActual < foodMax)
			eat();
		move();
		drawState();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void Wolf::eat(){

}
void Wolf::move(){
	Sheep* closestSheep = findClosestSheep();
	moveToClosestSheep(closestSheep);
}

std::string Wolf::getState(){
	if (_foodActual >= 0 && _foodActual <= 9)
		return "Wolf number: " + Unit::getName() + " Food:  " + std::to_string(_foodActual);
	else
		return "Wolf number: " + Unit::getName() + " Food: " + std::to_string(_foodActual);
}

void Wolf::drawState(){
	drawStateMutex.lock();
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvprintw(_number+10, (*_tableField).size() * 2 + 5, getState().c_str());
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
					if ((abs(this->_positionY - y) + abs(this->_positionX - x)) < distance){
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