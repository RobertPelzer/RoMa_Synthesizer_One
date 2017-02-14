#include "midiman.h"

using namespace std;

bool MidiMan::done;
vector<unsigned char>  a;
vector<unsigned char>  buffer;
vector<double>  Zeit;

MidiMan::MidiMan() {

    // rtmidid intit
	RtMidi::Api api = RtMidi::UNSPECIFIED;
	const std::string clientName = std::string("RtMidi Input Client");
	unsigned int queueSizeLimit = 100;

	midiin = new RtMidiIn(api,clientName,queueSizeLimit);	

    //
    unsigned int nPorts = midiin->getPortCount();

    midiin->openPort( 0 );
    //    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );
    done = false;
	isVerbose = true;

	cout << "Started Midi Server!" << endl;

}

void MidiMan::setVerbose() {
    isVerbose = true;

}

midiMessage MidiMan::get_rtmidi() {
	midiMessage mm = {-1,-1,-1, 0, false};
    
    int nBytes = 1;

    /// this is kind of a dirty workaroud -
    /// we loop over all in-messages and take the last one:
    while(nBytes>0) {
		
		stamp=midiin->getMessage(&a);
		nBytes = a.size();

        /// only do something if bytes are received
        if(nBytes!=0) {      
            
			/// only give feedback if 'verbose-mode' is active
            if(isVerbose == true  ) {
                std::cout << "received " << nBytes << "Bytes: " ;

                for (int i=0; i<nBytes; i++ )
                    std::cout <<  i << " = " << (int)a[i] << " -- " ;

            }

            buffer.insert(buffer.begin(), {a[0], a[1], a[2]});
            Zeit.insert(Zeit.begin(), stamp);
            std::cout<<std::endl;
            //std::cout<<Zeit.size()<<std::endl;
        }

	sleep(0.01);
    
	}
    //nur wenn Buffer  mindestens eine Message hat
    if(buffer.size()>=3) {
		mm.byte3 = buffer.back();
		buffer.pop_back();
		mm.byte2 = buffer.back();
		buffer.pop_back();
		mm.byte1 = buffer.back();
		buffer.pop_back();
		mm.stamp=Zeit.back();
		Zeit.pop_back();
		std::cout<<mm.byte1<< mm.byte2<<mm.byte3<<"stamp :"<< mm.stamp<<std::endl;
    }
    
    return mm;
}




//////////////////////////////////////////////////////////////////
// FLUSH
//////////////////////////////////////////////////////////////////

void MidiMan::flushProcessedMessages() {
// vektor von val zu a geändert
   buffer.clear();

}


int MidiMan::getNumFaderMessages() {

    int v  = (int) val.size();

    return v;
}
