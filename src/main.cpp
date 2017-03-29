#include <signal.h>
#include "romasynthi.h"

// while exit condition
bool done = false;

// Signal Handler function
void exitSigHandler(int s) {
	printf("Caught signal %d ... Bye!\n",s);
	// set while exit condition true
	done = true; 

}

int main(int argc, char *argv[]) {
    
    // create synthesizer object/client
    RoMaSynthi *synth = new RoMaSynthi();

    // activate the client
    synth->start();

    // connect sine ports to stereo ports
    synth->connectToPhysical(0,0);		// connects out port 0 to physical destination port 0
    synth->connectToPhysical(0,1);		// connects out port 1 to physical destination port 1

	// Unix signal handling 
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = exitSigHandler;		// Set up the structure to specify the new action
	sigemptyset(&sigIntHandler.sa_mask);			// initialize and empty a signal set
	sigIntHandler.sa_flags = 0;						// Flags to modify the behavior of the handler, or 0
	sigaction(SIGINT, &sigIntHandler, NULL);

	while(!done) {
		synth->midiHandler();
		synth->oscHandler();
		synth->lfoHandler();
		
		usleep(5);
    }

    synth->disconnectOutPort(0);		// Disconnecting ports
    synth->close();						// stop client
    delete synth;						// dele synth object
    
	return 0;
}

