#pragma once
#include <vector>
#include "curses.h"
#include <random>
#include "Field.h"
class Map
{
    const static int startSheepCount = 5;
	const static int startWolfCount = 2;
    int _size;
	std::vector<std::vector<Field>> tableField;
	std::vector<std::thread> underTakerThreads;
    void spawnSheep(int number);
	void spawnWolf(int number);
	void underTaker(Unit* unit);
	bool isEndOfTheWorld;
public:
	static int randomInt(int from, int to);
	
    Map(int rozmiar);
	~Map();
	void Spawn();
};

