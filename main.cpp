
#include "main.hpp"

//write 2byte binary data to a file
void writeWord(ofstream *, WORD);

int main(){

	//--------------------header chunk--------------------

    midiFile file("test.mid");

    //chunk type "MThd"
    file.writeLong("MThd");

     //length
    file.writeLong(6);

    //format 1...multi track
    file.writeWord(1);

    //number of tracks
    file.writeWord(1);

    //division (this should be multiples of 96
    file.writeWord(960);

    //--------------------track chunk--------------------

    //chunk type "MTrk"
    file.writeLong("MTrk");

    //length
    file.writeLong((LONG)0);

    //----------body----------

   	/*
		delta time
		event
		.
		.
		.
		delta time
		event
   	*/

    file.writeWord((WORD)0);
    file.setTempo(120);
    file.writeWord((WORD)0);
    file.setTimeSignature(4, 2, 24, 8);

}