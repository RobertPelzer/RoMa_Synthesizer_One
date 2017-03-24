#ifndef OSCICONTAINER_H
#define OSCICONTAINER_H

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
	
	Sawtoothwave *lfoSaw;
	Squarewave *lfoSquare;
	Sinusoid *lfoSin;

	double osciSawAmpl;
	double osciSquareAmpl;
	double osciNoiseAmpl;
	double osciSineAmpl;
	bool isLFO;
	int type;


public:
	Oscicontainer();
	// constructor for lfo oscillator
	Oscicontainer(int type, double f);
	

	// Setters
	void amplitude(double a);
	void frequency(double f);
	void setSawAmpl(double a);
	void setSquareAmpl(double a);
	void setNoiseAmpl(double a);
	void setSineAmpl(double a);
	void setLFOtype(int Type);

	// Getters
    double getNextSample();
    double getCurrentAmpl();
};

#endif // OSCICONTAINER_H
