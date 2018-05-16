
#include "main.hpp"

//write 2byte binary data to a file
void writeWord(ofstream *, WORD);

int main(){

    midiFile file("test.mid");

    file.write1Byte(0x4d);
    file.write1Byte(0x54);
    file.write1Byte(0x68);
    file.write1Byte(0x64);

    /*
    BYTE data = 0x4d;
    ofile.write((char *) &data, sizeof(data));
    data = 0x54;
    ofile.write((char *) &data, sizeof(data));
    data = 0x68;
    ofile.write((char *) &data, sizeof(data));
    data = 0x64;
    ofile.write((char *) &data, sizeof(data));
    */
/*
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

   	
		delta time
		event
		.
		.
		.
		delta time
		event
   	

    //delta time
    writeWord(&ofile, 0x03c0);

    //meta event
    writeWord(&ofile, 0x8n00);
*/

}
/*
void writeBytes(){
	BYTE byte;

	byte &= char[]
}
*/
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