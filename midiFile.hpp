#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long ULONGLONG;

using namespace std;

class midiFile{
	private:
		ofstream file;
		DWORD dataLength;
		ULONGLONG dataLengthPosition;
	public:
		midiFile(string fileName);
		~midiFile();
		void write(ULONGLONG data, BYTE size);
		void write(string data);
		void setDeltaTime(DWORD time); //max 7byte
		void noteOn(BYTE channel, BYTE noteNumber, BYTE velocity);
		void noteOff(BYTE channel, BYTE noteNumber, BYTE velocity);
		void setTrackName(string trackName);
		void setTempo(WORD tempo);
		void setTimeSignature(BYTE numerator, BYTE denominator, BYTE metronome, BYTE thirtySecondNotePerQuaterNote); // denominator ... 2 ^(-n)
		void setBeginOfTrack();
		void setEndOfTrack();
};

#endif