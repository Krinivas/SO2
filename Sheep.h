#pragma once
#include <mutex>
#include <thread>

class Sheep
{
    
	std::vector<std::vector<Field>>* _tableField;
    int _positionX;
    int _positionY;
    static std::mutex moveMutex;
    void run();
public:
	Sheep(std::vector<std::vector<Field>>* tableField,
            int positionY,
            int positionX);

	~Sheep();
};

