all:
	 g++ -Wall -Iinclude src/*.cpp -o game
	 ./game

build:
	 g++ -Wall -Iinclude src/*.cpp -o game

run:
	 ./game

clean:
	 rm game