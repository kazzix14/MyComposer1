
#include "main.hpp"

//write 2byte binary data to a file
void writeWord(ofstream *, WORD);

int main(){

	//--------------------header chunk--------------------

    midiFile file("test.mid");

    //chunk type "MThd"
    file.write("MThd");

     //length
    file.write(6, 4);

    //format 1...multi track
    file.write(1, 2);

    //number of tracks
    file.write(2, 2);

    //division (this should be multiples of 96
    file.write(960, 2);

    //--------------------track chunk--------------------

    file.setBeginOfTrack();

    file.setDeltaTime(0);
    file.setTrackName("midi_export");

    file.setDeltaTime(0);
    file.setTimeSignature(4, 2, 24, 8);

    file.setDeltaTime(0);
    file.setTempo(120);

    file.setEndOfTrack();



    file.setBeginOfTrack();

    file.setDeltaTime(0);
    file.setTrackName("unko");

    file.setDeltaTime(960);
    file.noteOn(0, 36, 100);
    file.setDeltaTime(960);
    file.noteOff(0, 36, 00);

    file.setEndOfTrack();

}