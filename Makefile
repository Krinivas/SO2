all:
	g++ -std=c++11 -c -o Field.o Field.cpp -lncurses -pthread
	g++ -std=c++11 -c -o Map.o Map.cpp -lncurses -pthread
	g++ -std=c++11 -c -o Sheep.o Sheep.cpp -lncurses -pthread
	g++ -std=c++11 -c -o Farm.o Farm.cpp -lncurses -pthread
	g++ -std=c++11 -o farm Farm.o Sheep.o Map.o Field.o -lncurses -pthread
