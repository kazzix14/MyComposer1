# Makefile
MyComposer: main.o midiFile.o
	g++ midiFile.o main.o -o MyComposer.exe
midiFile.o: midiFile.cpp
	g++ -c midiFile.cpp
main.o: main.cpp
	g++ -c main.cpp