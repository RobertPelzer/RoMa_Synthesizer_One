#include "noise.h"

Noise::Noise(double a) {
    amp     = a;
}

double Noise::getNextSample() {

    /// This method gets the next sample of the Sawtoothwave.
    /// The amplitude is applied and the angle of the
    /// Sawtoothwave is increased, according to the sample rate.

    // get Sawtoothwave value
	double thisVal = 0.0;

    // apply amplitude
	
	float a = -amp; 
	float b = amp;

	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	thisVal = a + r;

    // wrap to 2 pi

    return thisVal;

}


double Noise::amplitude() {
    return amp;
}

void Noise::amplitude(double a) {
    amp = a;
}
