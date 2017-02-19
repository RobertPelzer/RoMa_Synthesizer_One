//#include <iostream>
//#include <stdlib.h>
//#include <unistd.h>
//#include <cmath>
//#include <jackaudioio.hpp>
//#include <vector>
//#include <algorithm>

//#include "sawtoothwave.h"
//#include "noise.h"
//#include "sinusoid.h"
//#include "midiman.h"
#include <signal.h>

#include "romasynthi.h"

//using namespace std;

bool done = false;

// Signal Handler function
void exitSigHandler(int s) {
	printf("Caught signal %d ... Bye!\n",s);
	// set while exit condition true
	done = true; 

}

int main(int argc, char *argv[]) {
    
    
    RoMaSynthi *synth = new RoMaSynthi();


    /// activate the client
    synth->start();

    /// connect sine ports to stereo ports
    synth->connectToPhysical(0,0);		// connects out port 0 to physical destination port 0
    synth->connectToPhysical(0,1);		// connects out port 1 to physical destination port 1

    /// flush all messages
    //midiMan->flushProcessedMessages();
    
	// Unix signal handling 
	struct sigaction sigIntHandler;

	// Set up the structure to specify the new action
	sigIntHandler.sa_handler = exitSigHandler;
	// initialize and empty a signal set
	sigemptyset(&sigIntHandler.sa_mask);
	// Flags to modify the behavior of the handler, or 0
	sigIntHandler.sa_flags = 0;

	// 
	sigaction(SIGINT, &sigIntHandler, NULL);


	//double valOld = 0.0;
	//string typeOld = "";
	//string pathOld = "";

	while(!done) {
		synth->midiHandler();
		synth->oscHandler();
		usleep(5);
    }

    /// never reached:!=
    synth->disconnectOutPort(0);	// Disconnecting ports.
    synth->close();	// stop client.
    delete synth;	// always clean up after yourself.
    
	return 0;
}

