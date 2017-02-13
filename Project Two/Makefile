all: main.o
	g++ -std=c++1y main.o -o Blocksworld
main.o: main.cpp File.h Node.h
	g++ -std=c++1y -c -g main.cpp
clean:
	rm *.o Blocksworld
