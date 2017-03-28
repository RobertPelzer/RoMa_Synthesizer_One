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

using namespace std;

class RoMaSynthi: public JackCpp::AudioIO {

private:

	Oscicontainer **osci;
	OscMan *osc;
	MidiMan *midi;
	Biquad *filter;
	Oscicontainer *lfo;

	double t_tracking; //Zeit Counter
	int counter; //counter fue die Anzahl benutzer Oszillatoren
	int maxAnzahl_Osci;

	vector<int> Noten;
	vector<int> freeOsci;
	vector<double> timetracker;

	double valOld;
	string typeOld;
	string pathOld;
	double lfo_oldValue=0;

public:
    //MidiMan *midiMan;
    /// Audio Callback Function:
    /// - the output buffers are filled here
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
