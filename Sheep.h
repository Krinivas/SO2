#pragma once
#include <mutex>
#include <thread>
#include <vector>

#include "Unit.h"

class Field;
class Wolf;
class Sheep : public Unit
{
protected:
	
	friend class Wolf;
    const static int foodMax = 20;
    const static int foodDefault = 5;
    
    void run();
    void eat();
    void move();
    
    bool isMoveUpBest();
    bool isMoveDownBest();
    bool isMoveRightBest();
    bool isMoveLeftBest();
    int getGrassUp();
    int getGrassDown();
    int getGrassRight();
    int getGrassLeft();

	void drawState();
	
public:
	std::string getType() override;
	std::string getState() override;
	Sheep(std::vector<std::vector<Field>>* tableField,
            int positionY,
            int positionX,
            int number);

	~Sheep();
};

