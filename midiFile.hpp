#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long LONG;

using namespace std;

class midiFile{
	private:
		ofstream file;
	public:
		midiFile(string fileName);
		~midiFile();
		void writeByte(BYTE data);
		void writeWord(WORD data);
		void writeWord(char data[2]);
		void writeLong(LONG data);
		void writeLong(char data[4]);
		void setTempo(WORD tempo);
		void setTimeSignature(BYTE numerator, BYTE denominator, BYTE metronome, BYTE thirtySecondNotePerQuaterNote); // denominator ... 2 ^(-n)
};

#endif