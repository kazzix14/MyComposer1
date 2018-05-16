#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;

using namespace std;

class midiFile{
	private:
		ofstream file;
	public:
		midiFile(string fileName);
		~midiFile();
		void write1Byte(BYTE data);
};

#endif