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

	releaseNote *relNote;

	double osciSawAmpl;
	double osciSquareAmpl;
	double osciNoiseAmpl;
	double osciSineAmpl;

public:
	Oscicontainer(uint32_t fs);

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

	// Getters
    double getNextSample();
    double getCurrentAmpl();
};

#endif // OSCICONTAINER_H
