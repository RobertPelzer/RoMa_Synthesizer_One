#include "noise.h"

Noise::Noise(double a) {
    amp     = a;
}

double Noise::getNextSample() {

    /// This method gets the next sample of the Noise signal.

	double thisVal = 0.0;

	float a = -amp; 
	float b = amp;

	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	thisVal = a + r;

	curr_ampl = thisVal;

    return thisVal;

}


double Noise::amplitude() {
    return amp;
}

void Noise::amplitude(double a) {
    amp = a;
}

double Noise::getCurrentAmpl() {
	return curr_ampl;
}
