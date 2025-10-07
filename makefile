all:
	 g++ -Wall -o game main.cpp Ship/Ship.cpp Grid/Grid.cpp
	 ./game

build:
	 g++ -Wall -o game main.cpp Ship/Ship.cpp Grid/Grid.cpp

run:
	 ./game

clean:
	 rm game