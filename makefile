CXX = g++
CFLAGS = -std=c++17 -O3 -pthread -Wall

main:
	${CXX} ${CFLAGS} main.cpp -o main

clean:
	rm -f *.o main
