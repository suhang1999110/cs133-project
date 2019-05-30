CC=g++
CFLAGS=-std=c++14

all: demo

demo: demo.cpp
	${CC} ${CFLAGS} demo.cpp -o demo -I../third_party $(shell python3-config --includes) $(shell python3-config --libs)

clean:
	rm -f demo

.PHONY: clean