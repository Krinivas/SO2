#pragma once
#include "Unit.h"
#include <cmath>
class Sheep;
class Wolf :
	public Unit
{
	void run();
	void eat();
	void hunt();


	const static int foodMax = 50;
	const static int foodDefault = 25;
	void drawState();
	
	Sheep* findClosestSheep();
	void moveToClosestSheep(Sheep* closestSheel);
	void tryToKillDatSheep(Sheep* closestSheep);
	void killDatSheep(Sheep* closestSheep);
public:
	std::string getType() override;
	std::string getState() override;
	Wolf(std::vector<std::vector<Field>>* tableField,
		int positionY,
		int positionX,
		int number);
	~Wolf();
};

