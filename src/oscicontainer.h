#ifndef OSCICONTAINER_H
#define OSCICONTAINER_H

#include <stdint.h>

#include "sawtoothwave.h"
#include "squarewave.h"
#include "noise.h"
#include "sinusoid.h"

class Oscicontainer {
private:
 	Sinusoid *osciSine;
	Sawtoothwave *osciSaw;
	Squarewave *osciSquare;
	Noise *osciNoise;

	double osciSawAmpl;
	double osciSquareAmpl;
	double osciNoiseAmpl;
	double osciSineAmpl;

public:
	Oscicontainer(uint32_t fs);

	// Setters
	void amplitude(double a);
	void frequency(double f);
	void setSawAmpl(double a);
	void setSquareAmpl(double a);
	void setNoiseAmpl(double a);
	void setSineAmpl(double a);

	// Getters
    double getNextSample();
};

#endif // OSCICONTAINER_H
