#ifndef ROMASYNTHI_H
#define ROMASYNTHI_H

#include <jackaudioio.hpp>
#include <algorithm>
#include <unistd.h>

#include "oscicontainer.h"
#include "oscman.h"
#include "midiman.h"

using namespace std;

class RoMaSynthi: public JackCpp::AudioIO {

private:

	Oscicontainer **osci;
	OscMan *osc;

	MidiMan *midi;

	jack_nframes_t fs;
	jack_nframes_t nframes;

	double t_tracking; //Zeit Counter
	int counter; //counter fue die Anzahl benutzer Oszillatoren
	int maxAnzahl_Osci;

	vector<int> Noten;
	vector<int> freeOsci;
	vector<double> timetracker;

	double valOld;
	string typeOld;
	string pathOld;

public:

    /// Constructor
    RoMaSynthi();

	virtual int audioCallback(jack_nframes_t nframes,
							audioBufVector inBufs,
							audioBufVector outBufs);

	void midiHandler();
	void oscHandler();
};

#endif // ROMASYNTHI_H
