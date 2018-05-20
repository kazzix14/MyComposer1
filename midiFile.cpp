#include "midiFile.hpp"

midiFile::midiFile(string fileName){
	//open file as binary file
	file.open(fileName, ios::binary | ios::out);

    //error check
    if(!file){
    	cout << "Failed to open file" << endl;
    	return;
    }
}

midiFile::~midiFile(){
	//close file
	file.close();
}

void midiFile::write(ULONGLONG data, BYTE size){
	for(int i = size-1; i >= 0; i--)
			file.write((char *) &data+i, sizeof(BYTE));
	dataLength += (int)size;
}

void midiFile::write(string data){
	file.write(data.c_str(), data.size());
	dataLength += data.size();
}

void midiFile::setDeltaTime(DWORD time){
	BYTE b1 = 0,
		 b2 = 0,
		 b3 = 0,
		 b4 = 0;

	//0000 0000 0000 0000 0000 0000 0000

	time &= 0x0fffffff;
	b1 = time & 0x7f;
	if((time & 0xfffff80) != 0){
		b2 = (time >> 7) & 0x7f;
		b2 |= 0x80;
		if(((time >> 7) & 0xfffff80) != 0){
			b3 = (time >> 14) & 0x7f;
			b3 |= 0x80;
			if(((time >> 14) & 0xfffff80) != 0){
				b4 = (time >> 21) & 0x7f;
				b4 |= 0x80;
				this->write(b4, 1);
			}
			this->write(b3, 1);
		}
		this->write(b2, 1);
	}
	this->write(b1, 1);

	/*
    	maximum 4bytes
		data ^ 0x7f != 0
		byte1 = (data & 0x7f) | 0x80
		data >> 7 ^ 0x7f == 0
		byte2 = (data >> 7 & 0x7f)

		if data is 960...0011 1100 0000
		data ^ 0x7f == 0011 1000 0000 != 0
		byte1 = (data & 0x7f) | 0x80 == 1100 0000
		data >> 7 ^ 0x7f == 0000 0111 ^ 0x7f == 0000 0000 == 0
		byte2 = (data >> 7 & 0x7f) == 0000 0111
    */
}

void midiFile::noteOn(BYTE channel, BYTE noteNumber, BYTE velocity){
	this->write(0x90 | (channel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(velocity, 1);
}

void midiFile::noteOff(BYTE channel, BYTE noteNumber, BYTE velocity){
	this->write(0x80 | (channel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(velocity, 1);
}

void midiFile::setTrackName(string trackName){
	this->write(0xff03, 2);
	this->write(trackName.size(), 1);
	this->write(trackName);
}

void midiFile::setTempo(WORD tempo){
	this->write(0xff5103, 3);
	this->write(60000000/tempo, 3);
}

void midiFile::setTimeSignature(BYTE numerator, BYTE denominator, BYTE metronome, BYTE thirtySecondNotePerQuaterNote){
	this->write(0xff5804, 3);
	this->write(numerator << 24 | denominator << 16 | metronome << 8 | thirtySecondNotePerQuaterNote, 4);
}

void midiFile::setBeginOfTrack(){
	//chunk type "MTrk"
    this->write("MTrk");

    //length
	dataLengthPosition = file.tellp();
	this->write(0x00, 4);

	dataLength = 0;
}

void midiFile::setEndOfTrack(){
	ULONGLONG nowPos;
	this->setDeltaTime(0);
	this->write(0xff2f00, 3);
	nowPos = file.tellp();
	file.seekp(dataLengthPosition);
	this->write(dataLength, 4);
	file.seekp(nowPos);
}