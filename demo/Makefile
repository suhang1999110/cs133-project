CC=g++
CFLAGS=-std=c++14

all: demo

demo: demo.cpp
	${CC} ${CFLAGS} demo.cpp -o demo -I../third_party $(shell python3-config --includes) $(shell python3-config --libs)

clean:
	rm -f demo 0.txt 1.txt 2.txt 3.txt 4.txt 5.txt 6.txt 7.txt 8.txt 9.txt

.PHONY: clean