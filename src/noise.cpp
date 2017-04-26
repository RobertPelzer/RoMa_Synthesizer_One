//class Noise
//
// Noise sginal is generated numerically with random values

#include "noise.h"

Noise::Noise(double a) {
    amp     = a;
}

double Noise::getNextSample() {

    /// This method gets the next sample of the Noise signal.

	double thisVal = 0.0;

	float a = -amp; 
	float b = amp;

	// generates random float number between 0 an 1
	float random = ((float) rand()) / (float) RAND_MAX;
	// defines signal range
	float diff = b - a;

	// random number is caled to signal range (-1 to 1)
	float r = random * diff;
	thisVal = a + r;

	curr_ampl = thisVal;

    return thisVal;

}

//getter methods
double Noise::amplitude() {
    return amp;
}

double Noise::getCurrentAmpl() {

	return curr_ampl;
}

//setter methods
void Noise::amplitude(double a) {
    amp = a;
}




