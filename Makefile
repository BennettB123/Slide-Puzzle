compile:
	c++ -Wall -g -std=c++11 *.cpp -o slidePuzzle.out -lncurses
run:
	./slidePuzzle.out
clean:
	rm -f slidePuzzle.out
