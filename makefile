# Makefile
MyComposer: main.o midiFile.o
	g++ main.o midiFile.o -o MyComposer.exe
main.o: main.cpp
	g++ -c main.cpp
midiFile.o: midiFile.cpp
	g++ -c midiFile.cpp