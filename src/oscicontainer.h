#ifndef OSCICONTAINER_H
#define OSCICONTAINER_H

#include "sawtoothwave.h"
#include "squarewave.h"
#include "noise.h"

class Oscicontainer {
private:

	Sawtoothwave *osciSaw;
	Squarewave *osciSquare;
	Noise *osciNoise;

	double osciSawAmpl;
	double osciSquareAmpl;
	double osciNoiseAmpl;

public:
	Oscicontainer();


	// Setters
	void amplitude(double a);
	void frequency(double f);
	void setSawAmpl(double a);
	void setSquareAmpl(double a);
	void setNoiseAmpl(double a);

	// Getters
    double getNextSample();
};

#endif // OSCICONTAINER_H
