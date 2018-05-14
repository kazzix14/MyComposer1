#include<iostream>
#include<fstream>

#define DEBUG

using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;

//write 2byte binary data to a file
void writeWord(ofstream *, WORD);

int main(){

	//open file test.mid
    ofstream ofile("test.mid", ios::binary | ios::out);

    //error check
    if(!ofile){
    	cout << "Failed to open file" << endl;
    	return 1;
    }

    //--------------------header chunk--------------------

    //chunk type "MThd"
    writeWord(&ofile, 0x4d54);
    writeWord(&ofile, 0x6864);

    //length
    writeWord(&ofile, 0x0000);
    writeWord(&ofile, 0x0006);

    //format "01" (multi track)
    writeWord(&ofile, 0x0001);

    //number of tracks
    writeWord(&ofile, 0x0001);

    //division 0x03c0...960 (it should be multiples of 96
    writeWord(&ofile, 0x03c0);

    //--------------------track chunk--------------------

    //chunk type "MTrk"
    writeWord(&ofile, 0x4d54);
    writeWord(&ofile, 0x726b);

    //length
    writeWord(&ofile, 0x0000);/////////////////////////////////////
    writeWord(&ofile, 0x0000);

    //----------body----------

    //delta time
    writeWord(&ofile, 0x03c0);

    //event
    writeWord(&ofile, 0x8n00);

    ofile.close();

}

void writeWord(ofstream *ofile, WORD datal){

	WORD datab;

    //covert little endian to big endian
    datab = datal << 8;
    datab |= datal >> 8;

    #ifdef DEBUG
    cout << datal << " " << endl;
    #endif

    //write data
    ofile->write((char *) &datab, sizeof(datab));

	return;
}