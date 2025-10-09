all:
	 g++ -std=c++17 -Wall -Iinclude main.cpp src/*.cpp -o game
	 ./game

build:
	 g++ -std=c++17 -Wall -Iinclude main.cpp src/*.cpp -o game

run:
	 ./game

clear_logs:
	 rm ./logs/*.txt

clean:
	 rm game