#pragma once
#include "Unit.h"
#include <cmath>
class Sheep;
class Wolf :
	public Unit
{
	void run();
	void eat();
	void move();


	const static int foodMax = 99;
	const static int foodDefault = 50;
	void drawState();
	
	Sheep* findClosestSheep();
	void moveToClosestSheep(Sheep* closestSheel);
public:
	std::string getType() override;
	std::string getState() override;
	Wolf(std::vector<std::vector<Field>>* tableField,
		int positionY,
		int positionX,
		int number);
	~Wolf();
};

