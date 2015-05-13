#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include "Field.h"

class Field;
class Sheep
{
	std::vector<std::vector<Field>>* _tableField;
    int _positionX;
    int _positionY;
    std::string _name;
	int _number;
    static std::mutex moveMutex;
	static std::mutex drawStateMutex;
    const static int foodMax = 20;
    const static int foodDefault = 5;
    int _foodActual;
    void run();
    std::thread _runThread;
    int food;
    void eat();
    void die();
    void move();
    bool _died;
    bool isMoveUpBest();
    bool isMoveDownBest();
    bool isMoveRightBest();
    bool isMoveLeftBest();
    int getGrassUp();
    int getGrassDown();
    int getGrassRight();
    int getGrassLeft();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

	void drawState();
public:
	Sheep(std::vector<std::vector<Field>>* tableField,
            int positionY,
            int positionX,
            int number);

	~Sheep();
    std::string getName();
	std::string getState();
	int getActualFood();
	int getNumber();
    bool isDied();
};

