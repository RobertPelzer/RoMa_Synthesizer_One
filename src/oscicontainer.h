#ifndef OSCICONTAINER_H
#define OSCICONTAINER_H

#include <stdint.h>
#include <iostream>

#include "sawtoothwave.h"
#include "squarewave.h"
#include "noise.h"
#include "sinusoid.h"
#include "releaseNote.h"

class Oscicontainer {
private:
 	Sinusoid *osciSine;
	Sawtoothwave *osciSaw;
	Squarewave *osciSquare;
	Noise *osciNoise;
	
	Sawtoothwave *lfoSaw;
	Squarewave *lfoSquare;
	Sinusoid *lfoSin;

	releaseNote *relNote;

	double osciSawAmpl;
	double osciSquareAmpl;
	double osciNoiseAmpl;
	double osciSineAmpl;
	bool isLFO;
	int type;


public:

	Oscicontainer(uint32_t fs);

	Oscicontainer(int type, double f);
	

	// Setters
	void amplitude(double a);
	void frequency(double f);
	void phase(double phi);
	void setSawAmpl(double a);
	void setSquareAmpl(double a);
	void setNoiseAmpl(double a);
	void setSineAmpl(double a);

	void setReleaseNoteState(int status);
	float releaseNoteProcess();

	void setLFOtype(int Type);


	// Getters
    double getNextSample();
    double getCurrentAmpl();
};

#endif // OSCICONTAINER_H
