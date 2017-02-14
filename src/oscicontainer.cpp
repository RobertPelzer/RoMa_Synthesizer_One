#include "oscicontainer.h"

Oscicontainer::Oscicontainer() {
    osciSine = new Sinusoid(440,0.0,0,44100);
	osciSaw = new Sawtoothwave(220,0.0,0,44100,4);
	osciSquare = new Squarewave(220,0.0,0,44100);
	osciNoise = new Noise(0.0);
}

double Oscicontainer::getNextSample() {

    /// This method gets the next sample of the sinusoid.
    /// The amplitude is applied and the angle of the
    /// sinusoid is increased, according to the sample rate.

    // get sinusoidal value
    double thisVal = osciSine->getNextSample();
	thisVal = thisVal + osciSaw->getNextSample();
	thisVal = thisVal + osciSquare->getNextSample();
	thisVal = thisVal + osciNoise->getNextSample();

    return thisVal;

}

void Oscicontainer::amplitude(double a) {
	//osciSine->amplitude(a);
	//osciSaw->amplitude(a);
	osciSquare->amplitude(a);
	//osciNoise->amplitude(a);
}

void Oscicontainer::frequency(double f) {
	//osciSine->frequency(f);
	//osciSaw->frequency(f);
	osciSquare->frequency(f);
}
