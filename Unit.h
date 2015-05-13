#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include <string>



class Field;
class Unit
{
protected:
	static std::mutex moveMutex;
	static std::mutex drawStateMutex;
	std::vector<std::vector<Field>>* _tableField;
	int _number;
	int _positionX;
	int _positionY;
	bool _died;
	std::string _name;
	int _foodActual;
	std::thread _runThread;


	void die();

	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	
public:
	virtual std::string getType() = 0;
	Unit(std::vector<std::vector<Field>>* tableField,
		int positionY,
		int positionX,
		int number);
	virtual ~Unit();

	bool isDied();
	std::string getName();
	virtual std::string getState() = 0;
	int getActualFood();
};

