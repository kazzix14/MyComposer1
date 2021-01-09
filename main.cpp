
#include "main.hpp"

int main(){

	//--------------------header chunk--------------------

    midiFile file("test.mid");

    file.setHeader(1, 960);

    //--------------------track chunk--------------------

    file.setBeginOfTrack();

    file.setTrackName("track1");
    file.setTimeSignature(4, 2, 24, 8);
    file.setTempo(120);

    file.setDeltaTime(8);
    file.noteOn(36, 100);
    file.setDeltaTime(8);
    file.noteOff(36);

    file.setEndOfTrack();

}