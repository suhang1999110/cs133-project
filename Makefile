CC=g++
CFLAGS=-std=c++14

all: demo

demo: demo.cpp
	${CC} ${CFLAGS} demo.cpp -o demo

clean:
	rm -f demo

.PHONY: clean