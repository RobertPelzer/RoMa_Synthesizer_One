/**
 * \file
 *
 * \brief This is an example of creating a sawtoothwave.
 *
 *
 * \todo Use interpolation!
 *
 * \author
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/18$
 *
 * Contact: von_coler@tu-berlin.de
 *
 */



#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <jackaudioio.hpp>

#include "sawtoothwave.h"
#include "midiman.h"

using std::cout;
using std::endl;



class SimpleSaw: public JackCpp::AudioIO {

private:

    Sawtoothwave *saw1;
    MidiMan *midiMan;

public:
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){


        /// process midi messages
		MidiMan::midiMessage mm = midiMan->get_rtmidi();



        if(mm.byte1 != -1)
        {

            double f0 = std::pow((double) mm.byte3 / 126.0,4.0) * 1000.0;
             /// flush all messages
            midiMan->flushProcessedMessages();

            saw1->frequency(f0);

        }




        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {

            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {

                outBufs[0][frameCNT] = saw1->getNextSample();
            }
        }

        ///return 0 on success
        return 0;
    }

    /// Constructor
    SimpleSaw(double f1) :
        JackCpp::AudioIO("sawtoothwave_example", 0,1){

        reserveInPorts(2);
        reserveOutPorts(2);




        saw1        = new Sawtoothwave(f1,0.5,1,44100,2);

        /// allocate a new midi manager
        midiMan = new MidiMan();

    }

};

///
///
///
int main(int argc, char *argv[]){


    double f1 = 60.0;

    /// initial ports from constructor created here.
    SimpleSaw * t = new SimpleSaw(f1);



    /// activate the client
    t->start();

    /// connect sine ports to stereo ports
    t->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
    t->connectToPhysical(0,1);		// connects this client out port 1 to physical destination port 1

    ///print names
    cout << "outport names:" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;

    /// run for EVER
    sleep(-1);

    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}

