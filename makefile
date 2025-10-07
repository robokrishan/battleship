all:
	 g++ -Wall -o game main.cpp Ship/Ship.cpp Grid/Grid.cpp Player.cpp Battleship.cpp
	 ./game

build:
	 g++ -Wall -o game main.cpp Ship/Ship.cpp Grid/Grid.cpp Player.cpp Battleship.cpp

run:
	 ./game

clean:
	 rm game