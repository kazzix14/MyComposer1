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
		BYTE curentChannel;
		WORD numOfTracks;
		WORD timeDivision;
		DWORD dataLength;
		ULONGLONG dataLengthPosition;
	public:
		midiFile(string fileName);
		~midiFile();
		void write(ULONGLONG data, BYTE size);
		void write(string data);
		void setDeltaTime(WORD note); //max 7byte
		void setDeltaTime(WORD note, BYTE times); //max 7byte
		void noteOn(BYTE channel, BYTE noteNumber, BYTE velocity);
		void noteOn(BYTE noteNumber, BYTE velocity);
		void noteOff(BYTE channel, BYTE noteNumber, BYTE velocity);
		void noteOff(BYTE noteNumber, BYTE velocity);
		void noteOff(BYTE noteNumber);
		void setMidiChannel(BYTE channel);
		void setTrackName(string trackName);
		void setTempo(WORD tempo);
		void setTimeSignature(BYTE numerator, BYTE denominator, BYTE metronome, BYTE thirtySecondNotePerQuaterNote); // denominator ... 2 ^(-n)
		void setHeader(BYTE format, WORD timeDivision);
		void setBeginOfTrack();
		void setEndOfTrack();
		WORD getTimeDivision();
};

#endif