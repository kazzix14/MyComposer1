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
	//clos file
	file.close();
}

void midiFile::writeByte(BYTE data){
	//write data to flie
	file.write((char *) &data, sizeof(BYTE));
}

void midiFile::writeWord(WORD data){
	//write data to flie
	file.write((char *) &data+1, sizeof(BYTE));
	file.write((char *) &data, sizeof(BYTE));
}

void midiFile::writeWord(char data[2]){
	//write data to flie
	file.write((char *) data, sizeof(BYTE));
	file.write((char *) data+1, sizeof(BYTE));
}

void midiFile::writeLong(LONG data){
	//write data to flie
	file.write((char *) &data+3, sizeof(BYTE));
	file.write((char *) &data+2, sizeof(BYTE));
	file.write((char *) &data+1, sizeof(BYTE));
	file.write((char *) &data, sizeof(BYTE));
}

void midiFile::writeLong(char data[4]){
	//write data to flie
	file.write((char *) data, sizeof(BYTE));
	file.write((char *) data+1, sizeof(BYTE));
	file.write((char *) data+2, sizeof(BYTE));
	file.write((char *) data+3, sizeof(BYTE));
}

void midiFile::setTempo(WORD tempo){
	this->writeByte(0xFF);
	this->writeByte(0x51);
	this->writeLong(0x03000000 | (tempo & 0x00ffffff));
}

void midiFile::setTimeSignature(BYTE numerator, BYTE denominator, BYTE metronome, BYTE thirtySecondNotePerQuaterNote){
	cout << '0'+numerator << " " << '0'+denominator << " " << '0'+metronome << " " << '0'+thirtySecondNotePerQuaterNote << endl;
	this->writeByte(0xFF);
	this->writeByte(0x58);
	this->writeLong(numerator << 24 | denominator << 16 | metronome << 8 | thirtySecondNotePerQuaterNote);
}