CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -std=c99
CXXFLAGS=-Wall -Wextra -std=c++14

all: bin/weight bin/index

bin:
	mkdir -p bin

bin/weight: src/weight.c | bin
	$(CC) $(CFLAGS) -o bin/weight src/weight.c

bin/index: src/index.cpp | bin
	$(CXX) $(CXXFLAGS) -o bin/index src/index.cpp

test: all
	rm -f records.dat
	./bin/weight config/weights.conf records.dat JIU_C "系統核心架構測試"
	./bin/weight config/weights.conf records.dat JIU_ES "Termux測試環境"
	./bin/weight config/weights.conf records.dat JIU_W "商業計畫架構"
	./bin/index records.dat

clean:
	rm -rf bin records.dat

.PHONY: all test clean
