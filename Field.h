#pragma once
#include "Sheep.h"
#include "Wolf.h"
//#include "Unit.h"
#include "curses.h"
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
class Map;
class Sheep;

class Field
{
    friend class Map;
    friend class Sheep;
	friend class Unit;
	friend class Wolf;
	static bool isEndOfTheWorld;
	int _positionX;
	int _positionY;
	int _grassLevel;
	std::string _sign;
	Unit* _unit;
    std::thread _runThread;
    static std::mutex grassMutex;
public:
	const static int maxGrass = 1;
	const static int startGrass = 5;
    Field();
	~Field();
	void setPosition(int x, int y);
	void drawColored();
	void setSign(std::string sign);
    void run();
    int getGrassLevel();
	bool isSomethingDead();
	
};

