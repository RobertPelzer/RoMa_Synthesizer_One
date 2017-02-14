#ifndef ROMASYNTHI_H
#define ROMASYNTHI_H

#include <algorithm>
#include <jackaudioio.hpp>
#include <vector>

#include "oscicontainer.h"
#include "oscman.h"
#include "midiman.h"

using namespace std;

class RoMaSynthi: public JackCpp::AudioIO {

private:

	Oscicontainer **osci;
	OscMan *osc;
	MidiMan *midi;

	double t_tracking; //Zeit Counter
	int counter; //counter fue die Anzahl benutzer Oszillatoren
	int maxAnzahl_Osci;

	vector<int> Noten;
	vector<int> freeOsci;
	vector<double> timetracker;


public:
    //MidiMan *midiMan;
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs) {

        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {

            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {

                outBufs[0][frameCNT] = (osci[0]->getNextSample() +
										osci[1]->getNextSample() + 
										osci[2]->getNextSample() +
										osci[3]->getNextSample() +
										osci[4]->getNextSample()) / 5;
			}
        }

        ///return 0 on success

        return 0;
	};

    /// Constructor
    RoMaSynthi();

	// Setters
	


	void midiHandler();
};

#endif // ROMASYNTHI_H
