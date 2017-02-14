#ifndef OSCICONTAINER_H
#define OSCICONTAINER_H

//#include<vector>
//#include<cmath>

#include "sinusoid.h"
#include "sawtoothwave.h"
#include "squarewave.h"
#include "noise.h"

class Oscicontainer {
private:

	Sinusoid *osciSine;
	Sawtoothwave *osciSaw;
	Squarewave *osciSquare;
	Noise *osciNoise;

public:
	Oscicontainer();


	// Setters
	void amplitude(double a);
	void frequency(double f);

	// Getters
    double getNextSample();
};

#endif // OSCICONTAINER_H
