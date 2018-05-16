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

void midiFile::write1Byte(BYTE data){
	//write data to flie
	file.write((char *) &data, sizeof(data));
}