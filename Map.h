#pragma once
#include <vector>
#include <ncurses.h>
#include "Field.h"
class Map
{
	int _rozmiar;
	std::vector<std::vector<Field>> tableField;
public:
	Map(int rozmiar);
	~Map();
	void Init();
};

