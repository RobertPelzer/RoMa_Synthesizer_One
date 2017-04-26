#ifndef ROMASYNTHI_H
#define ROMASYNTHI_H

#include <jackaudioio.hpp>
#include <algorithm>
#include <unistd.h>

#include "oscicontainer.h"
#include "oscman.h"
#include "midiman.h"
#include "Biquad.h"
#include "sinusoid.h"
#include "distortion.h"
#include "adsr.h"

using namespace std;

class RoMaSynthi: public JackCpp::AudioIO {

private:

	Oscicontainer **osci;
	OscMan *osc;

	MidiMan *midi;
	Biquad *filter;
	Oscicontainer *lfo;
	Distortion* distortion;

	bool filterStatus;

	jack_nframes_t fs;
	jack_nframes_t nframes;

	// variables for midi handling
	double t_tracking; //time tracker
	int counter; //counter for the number of used oscillators
	int maxAnzahl_Osci;// max number of availible oscillators

	// vecors for midi handling
	vector<int> Noten;
	vector<int> freeOsci;
	vector<double> timetracker;

	// variables for osc handling
	double valOld;
	string typeOld;
	string pathOld;
	double lfo_oldValue=0;

public:

    /// Declaration of Audio Callback Function:
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs); 

    /// Constructor
    RoMaSynthi();

	// Setters
	
 	void lfoHandler();
	void midiHandler();
	void oscHandler();
};

#endif // ROMASYNTHI_H
