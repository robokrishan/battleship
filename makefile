all:
	 g++ -std=c++17 -Wall -Iinclude src/*.cpp -o game
	 ./game

build:
	 g++ -std=c++17 -Wall -Iinclude src/*.cpp -o game

run:
	 ./game

clean:
	 rm game