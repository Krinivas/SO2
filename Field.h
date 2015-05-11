#pragma once
#include "Sheep.h"
#include <ncurses.h>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
class Map;

class Field
{
    friend class Map;
	int _positionX;
	int _positionY;
	int _grassLevel;
	std::string _sign;
	Sheep* _unit;
    std::thread _runThread;
    static std::mutex grassMutex;
public:
	const static int maxGrass = 20;
	const static int startGrass = 0;
    Field();
	~Field();
	void setPosition(int x, int y);
	void drawColored();
	void setSign(std::string sign);
    void run();
};

