#include "midiFile.hpp"

midiFile::midiFile(string fileName){
	file.open(fileName, ios::binary | ios::out);

    if(!file){
    	cout << "Failed to open file" << endl;
    	exit(-1);
    }

    this->numOfTracks = 0;
    this->curentChannel = 0;
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

void midiFile::setDeltaTime(WORD note){
	if(note != 0)
		note = this->timeDivision / note * 4;
	note &= 0x0fffffff;
	if((note & 0xfffff80) != 0)
		if(((note >> 7) & 0xfffff80) != 0)
			if(((note >> 14) & 0xfffff80) != 0)
				this->write(((note >> 21) & 0x7f) | 0x80, 1);
			this->write(((note >> 14) & 0x7f) | 0x80, 1);
		this->write(((note >> 7) & 0x7f) | 0x80, 1);
	this->write(note & 0x7f, 1);
}

void midiFile::setDeltaTime(WORD note, BYTE times){
	note = this->timeDivision / note * 4 * times;
	note &= 0x0fffffff;
	if((note & 0xfffff80) != 0)
		if(((note >> 7) & 0xfffff80) != 0)
			if(((note >> 14) & 0xfffff80) != 0)
				this->write(((note >> 21) & 0x7f) | 0x80, 1);
			this->write(((note >> 14) & 0x7f) | 0x80, 1);
		this->write(((note >> 7) & 0x7f) | 0x80, 1);
	this->write(note & 0x7f, 1);
}

void midiFile::noteOn(BYTE channel, BYTE noteNumber, BYTE velocity){
	this->write(0x90 | (channel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(velocity, 1);
}

void midiFile::noteOn(BYTE noteNumber, BYTE velocity){
	this->write(0x90 | (this->curentChannel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(velocity, 1);
}

void midiFile::noteOff(BYTE channel, BYTE noteNumber, BYTE velocity){
	this->write(0x80 | (channel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(velocity, 1);
}

void midiFile::noteOff(BYTE noteNumber, BYTE velocity){
	this->write(0x80 | (this->curentChannel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(velocity, 1);
}

void midiFile::noteOff(BYTE noteNumber){
	this->write(0x80 | (this->curentChannel && 0x0f), 1);
	this->write(noteNumber, 1);
	this->write(0x00, 1);
}

void midiFile::setMidiChannel(BYTE channel){
	this->curentChannel = channel;
}

void midiFile::setTrackName(string trackName){
	this->setDeltaTime(0);
	this->write(0xff03, 2);
	this->write(trackName.size(), 1);
	this->write(trackName);
}

void midiFile::setTempo(WORD tempo){
	this->setDeltaTime(0);
	this->write(0xff5103, 3);
	this->write(60000000/tempo, 3);
}

void midiFile::setTimeSignature(BYTE numerator, BYTE denominator, BYTE metronome, BYTE thirtySecondNotePerQuaterNote){
	this->setDeltaTime(0);
	this->write(0xff5804, 3);
	this->write(numerator << 24 | denominator << 16 | metronome << 8 | thirtySecondNotePerQuaterNote, 4);
}

void midiFile::setHeader(BYTE format, WORD timeDivision){
    //chunk type "MThd"
    this->write("MThd");

     //length
    this->write(6, 4);

    //format 1...multi track
    this->write(format, 2);

    //number of tracks ... fpos = 10
    this->write(1, 2);

    //timeDivision (this should be multiples of 96
    this->timeDivision = timeDivision;
    this->write(timeDivision, 2);
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

	numOfTracks++;
	//go to numtrack
	file.seekp(10);
	this->write(numOfTracks, 2);

	file.seekp(nowPos);
}

WORD midiFile::getTimeDivision(){
	return this->timeDivision;
}