CC=g++
CFLAGS=-std=c++14

all: demo

demo: demo.cpp
	${CC} ${CFLAGS} third_party/CJsonObject/CJsonObject.cpp third_party/CJsonObject/cJSON.c demo.cpp -o demo

clean:
	rm -f demo

.PHONY: clean