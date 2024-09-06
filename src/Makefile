CC= g++
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests/*.cc

all: rebuild

main: test

test: clean
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

rebuild: clean main

check: test
	clang-format -style=Google -i headers/*.h
	clang-format -style=Google -i tests/*.cc
	leaks --atExit -- ./test

clean:
	rm -rf *.o *.a *.out report test
