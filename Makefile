all: intersection
intersection: geometry.o main.o 
	g++ -o intersection geometry.o main.o -lGL -lGLU -lglut
geometry.o: geometry.cpp
	g++ -o geometry.o -c geometry.cpp
main.o: main.cpp geometry.h
	g++ -o main.o -c main.cpp -lGL -lGLU -lglut