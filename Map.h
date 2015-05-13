#pragma once
#include <vector>
#include "curses.h"
#include <random>
#include "Field.h"
class Map
{
    const static int startSheepCount = 1;
	const static int startWolfCount = 1;
	static std::mutex unitMutex;
    int _size;
	std::vector<std::vector<Field>> tableField;
    void spawnSheep(int number);
	void spawnWolf(int number);
public:
	static int randomInt(int from, int to);
    Map(int rozmiar);
	~Map();
	void Init();
};

